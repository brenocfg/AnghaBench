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
struct special_params {int clk_src; int dig_in_fmt; int dig_out_fmt; int clk_lock; scalar_t__ ctl_id_sync; } ;
struct snd_bebob {int /*<<< orphan*/  card; int /*<<< orphan*/  unit; int /*<<< orphan*/  tx_stream; int /*<<< orphan*/  rx_stream; struct special_params* maudio_special_quirk; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 scalar_t__ amdtp_stream_running (int /*<<< orphan*/ *) ; 
 int fcp_avc_transaction (int /*<<< orphan*/ ,int*,int,int*,int,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
avc_maudio_set_special_clk(struct snd_bebob *bebob, unsigned int clk_src,
			   unsigned int dig_in_fmt, unsigned int dig_out_fmt,
			   unsigned int clk_lock)
{
	struct special_params *params = bebob->maudio_special_quirk;
	int err;
	u8 *buf;

	if (amdtp_stream_running(&bebob->rx_stream) ||
	    amdtp_stream_running(&bebob->tx_stream))
		return -EBUSY;

	buf = kmalloc(12, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	buf[0]  = 0x00;		/* CONTROL */
	buf[1]  = 0xff;		/* UNIT */
	buf[2]  = 0x00;		/* vendor dependent */
	buf[3]  = 0x04;		/* company ID high */
	buf[4]  = 0x00;		/* company ID middle */
	buf[5]  = 0x04;		/* company ID low */
	buf[6]  = 0xff & clk_src;	/* clock source */
	buf[7]  = 0xff & dig_in_fmt;	/* input digital format */
	buf[8]  = 0xff & dig_out_fmt;	/* output digital format */
	buf[9]  = 0xff & clk_lock;	/* lock these settings */
	buf[10] = 0x00;		/* padding  */
	buf[11] = 0x00;		/* padding */

	err = fcp_avc_transaction(bebob->unit, buf, 12, buf, 12,
				  BIT(1) | BIT(2) | BIT(3) | BIT(4) |
				  BIT(5) | BIT(6) | BIT(7) | BIT(8) |
				  BIT(9));
	if ((err > 0) && (err < 10))
		err = -EIO;
	else if (buf[0] == 0x08) /* NOT IMPLEMENTED */
		err = -ENOSYS;
	else if (buf[0] == 0x0a) /* REJECTED */
		err = -EINVAL;
	if (err < 0)
		goto end;

	params->clk_src		= buf[6];
	params->dig_in_fmt	= buf[7];
	params->dig_out_fmt	= buf[8];
	params->clk_lock	= buf[9];

	if (params->ctl_id_sync)
		snd_ctl_notify(bebob->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       params->ctl_id_sync);

	err = 0;
end:
	kfree(buf);
	return err;
}