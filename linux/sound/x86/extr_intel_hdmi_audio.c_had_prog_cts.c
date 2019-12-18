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
typedef  int u64 ;
typedef  int u32 ;
struct snd_intelhad {int /*<<< orphan*/  dev; scalar_t__ dp_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_HDMI_CTS ; 
 int BIT (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int div64_u64 (int,int) ; 
 int had_calculate_maud_value (int,int) ; 
 int /*<<< orphan*/  had_write_register (struct snd_intelhad*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void had_prog_cts(u32 aud_samp_freq, u32 tmds, u32 link_rate,
			 u32 n_param, struct snd_intelhad *intelhaddata)
{
	u32 cts_val;
	u64 dividend, divisor;

	if (intelhaddata->dp_output) {
		/* Substitute cts_val with Maud according to DP 1.2 spec*/
		cts_val = had_calculate_maud_value(aud_samp_freq, link_rate);
	} else {
		/* Calculate CTS according to HDMI 1.3a spec*/
		dividend = (u64)tmds * n_param*1000;
		divisor = 128 * aud_samp_freq;
		cts_val = div64_u64(dividend, divisor);
	}
	dev_dbg(intelhaddata->dev, "TMDS value=%d, N value=%d, CTS Value=%d\n",
		 tmds, n_param, cts_val);
	had_write_register(intelhaddata, AUD_HDMI_CTS, (BIT(24) | cts_val));
}