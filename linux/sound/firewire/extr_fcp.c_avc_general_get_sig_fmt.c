#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct fw_unit {int dummy; } ;
typedef  enum avc_general_plug_dir { ____Placeholder_avc_general_plug_dir } avc_general_plug_dir ;

/* Variables and functions */
 int AVC_GENERAL_PLUG_DIR_IN ; 
 int BIT (int) ; 
 unsigned int CIP_SFC_COUNT ; 
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int* amdtp_rate_table ; 
 int fcp_avc_transaction (struct fw_unit*,int*,int,int*,int,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 

int avc_general_get_sig_fmt(struct fw_unit *unit, unsigned int *rate,
			    enum avc_general_plug_dir dir,
			    unsigned short pid)
{
	unsigned int sfc;
	u8 *buf;
	int err;

	buf = kzalloc(8, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	buf[0] = 0x01;		/* AV/C STATUS */
	buf[1] = 0xff;		/* Unit */
	if (dir == AVC_GENERAL_PLUG_DIR_IN)
		buf[2] = 0x19;	/* INPUT PLUG SIGNAL FORMAT */
	else
		buf[2] = 0x18;	/* OUTPUT PLUG SIGNAL FORMAT */
	buf[3] = 0xff & pid;	/* plug id */
	buf[4] = 0x90;		/* EOH_1, Form_1, FMT. AM824 */
	buf[5] = 0xff;		/* FDF-hi. AM824, frequency */
	buf[6] = 0xff;		/* FDF-mid. AM824, SYT hi (not used) */
	buf[7] = 0xff;		/* FDF-low. AM824, SYT lo (not used) */

	/* do transaction and check buf[1-4] are the same against command */
	err = fcp_avc_transaction(unit, buf, 8, buf, 8,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4));
	if (err < 0)
		;
	else if (err < 8)
		err = -EIO;
	else if (buf[0] == 0x08) /* NOT IMPLEMENTED */
		err = -ENOSYS;
	else if (buf[0] == 0x0a) /* REJECTED */
		err = -EINVAL;
	else if (buf[0] == 0x0b) /* IN TRANSITION */
		err = -EAGAIN;
	if (err < 0)
		goto end;

	/* check sfc field and pick up rate */
	sfc = 0x07 & buf[5];
	if (sfc >= CIP_SFC_COUNT) {
		err = -EAGAIN;	/* also in transition */
		goto end;
	}

	*rate = amdtp_rate_table[sfc];
	err = 0;
end:
	kfree(buf);
	return err;
}