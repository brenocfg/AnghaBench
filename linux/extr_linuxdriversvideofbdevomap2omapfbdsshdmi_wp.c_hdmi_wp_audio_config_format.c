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
typedef  int /*<<< orphan*/  u32 ;
struct hdmi_wp_data {int /*<<< orphan*/  base; } ;
struct hdmi_audio_format {int /*<<< orphan*/  sample_size; int /*<<< orphan*/  samples_per_word; int /*<<< orphan*/  sample_order; int /*<<< orphan*/  justification; int /*<<< orphan*/  type; int /*<<< orphan*/  en_sig_blk_strt_end; int /*<<< orphan*/  active_chnnls_msk; int /*<<< orphan*/  stereo_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  HDMI_WP_AUDIO_CFG ; 
 scalar_t__ OMAPDSS_VER_OMAP4 ; 
 scalar_t__ OMAPDSS_VER_OMAP4430_ES1 ; 
 scalar_t__ OMAPDSS_VER_OMAP4430_ES2 ; 
 int /*<<< orphan*/  hdmi_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ omapdss_get_version () ; 

void hdmi_wp_audio_config_format(struct hdmi_wp_data *wp,
		struct hdmi_audio_format *aud_fmt)
{
	u32 r;

	DSSDBG("Enter hdmi_wp_audio_config_format\n");

	r = hdmi_read_reg(wp->base, HDMI_WP_AUDIO_CFG);
	if (omapdss_get_version() == OMAPDSS_VER_OMAP4430_ES1 ||
	    omapdss_get_version() == OMAPDSS_VER_OMAP4430_ES2 ||
	    omapdss_get_version() == OMAPDSS_VER_OMAP4) {
		r = FLD_MOD(r, aud_fmt->stereo_channels, 26, 24);
		r = FLD_MOD(r, aud_fmt->active_chnnls_msk, 23, 16);
	}
	r = FLD_MOD(r, aud_fmt->en_sig_blk_strt_end, 5, 5);
	r = FLD_MOD(r, aud_fmt->type, 4, 4);
	r = FLD_MOD(r, aud_fmt->justification, 3, 3);
	r = FLD_MOD(r, aud_fmt->sample_order, 2, 2);
	r = FLD_MOD(r, aud_fmt->samples_per_word, 1, 1);
	r = FLD_MOD(r, aud_fmt->sample_size, 0, 0);
	hdmi_write_reg(wp->base, HDMI_WP_AUDIO_CFG, r);
}