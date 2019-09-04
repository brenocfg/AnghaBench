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
typedef  int /*<<< orphan*/  u8 ;
struct rtl8xxxu_priv {int dummy; } ;

/* Variables and functions */

void rtl8xxxu_gen2_report_connect(struct rtl8xxxu_priv *priv,
				  u8 macid, bool connect)
{
#ifdef RTL8XXXU_GEN2_REPORT_CONNECT
	/*
	 * Barry Day reports this causes issues with 8192eu and 8723bu
	 * devices reconnecting. The reason for this is unclear, but
	 * until it is better understood, leave the code in place but
	 * disabled, so it is not lost.
	 */
	struct h2c_cmd h2c;

	memset(&h2c, 0, sizeof(struct h2c_cmd));

	h2c.media_status_rpt.cmd = H2C_8723B_MEDIA_STATUS_RPT;
	if (connect)
		h2c.media_status_rpt.parm |= BIT(0);
	else
		h2c.media_status_rpt.parm &= ~BIT(0);

	rtl8xxxu_gen2_h2c_cmd(priv, &h2c, sizeof(h2c.media_status_rpt));
#endif
}