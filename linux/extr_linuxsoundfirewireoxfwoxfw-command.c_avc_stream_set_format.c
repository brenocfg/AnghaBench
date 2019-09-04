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
 int BIT (int) ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int fcp_avc_transaction (struct fw_unit*,int*,unsigned int,int*,unsigned int,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,unsigned int) ; 

int avc_stream_set_format(struct fw_unit *unit, enum avc_general_plug_dir dir,
			  unsigned int pid, u8 *format, unsigned int len)
{
	u8 *buf;
	int err;

	buf = kmalloc(len + 10, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	buf[0] = 0x00;		/* CONTROL */
	buf[1] = 0xff;		/* UNIT */
	buf[2] = 0xbf;		/* EXTENDED STREAM FORMAT INFORMATION */
	buf[3] = 0xc0;		/* SINGLE subfunction */
	buf[4] = dir;		/* Plug Direction */
	buf[5] = 0x00;		/* UNIT */
	buf[6] = 0x00;		/* PCR (Isochronous Plug) */
	buf[7] = 0xff & pid;	/* Plug ID */
	buf[8] = 0xff;		/* Padding */
	buf[9] = 0xff;		/* Support status in response */
	memcpy(buf + 10, format, len);

	/* do transaction and check buf[1-8] are the same against command */
	err = fcp_avc_transaction(unit, buf, len + 10, buf, len + 10,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5) |
				  BIT(6) | BIT(7) | BIT(8));
	if (err < 0)
		;
	else if (err < len + 10)
		err = -EIO;
	else if (buf[0] == 0x08) /* NOT IMPLEMENTED */
		err = -ENOSYS;
	else if (buf[0] == 0x0a) /* REJECTED */
		err = -EINVAL;
	else
		err = 0;

	kfree(buf);

	return err;
}