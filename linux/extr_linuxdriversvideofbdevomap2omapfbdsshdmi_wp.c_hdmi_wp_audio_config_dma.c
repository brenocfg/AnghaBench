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
struct hdmi_audio_dma {int /*<<< orphan*/  fifo_threshold; int /*<<< orphan*/  mode; int /*<<< orphan*/  block_size; int /*<<< orphan*/  transfer_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  HDMI_WP_AUDIO_CFG2 ; 
 int /*<<< orphan*/  HDMI_WP_AUDIO_CTRL ; 
 int /*<<< orphan*/  hdmi_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hdmi_wp_audio_config_dma(struct hdmi_wp_data *wp,
		struct hdmi_audio_dma *aud_dma)
{
	u32 r;

	DSSDBG("Enter hdmi_wp_audio_config_dma\n");

	r = hdmi_read_reg(wp->base, HDMI_WP_AUDIO_CFG2);
	r = FLD_MOD(r, aud_dma->transfer_size, 15, 8);
	r = FLD_MOD(r, aud_dma->block_size, 7, 0);
	hdmi_write_reg(wp->base, HDMI_WP_AUDIO_CFG2, r);

	r = hdmi_read_reg(wp->base, HDMI_WP_AUDIO_CTRL);
	r = FLD_MOD(r, aud_dma->mode, 9, 9);
	r = FLD_MOD(r, aud_dma->fifo_threshold, 8, 0);
	hdmi_write_reg(wp->base, HDMI_WP_AUDIO_CTRL, r);
}