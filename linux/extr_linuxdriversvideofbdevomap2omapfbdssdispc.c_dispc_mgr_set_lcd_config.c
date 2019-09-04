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
struct dss_lcd_mgr_config {int /*<<< orphan*/  lcden_sig_polarity; int /*<<< orphan*/  video_port_width; int /*<<< orphan*/  clock_info; int /*<<< orphan*/  fifohandcheck; int /*<<< orphan*/  stallmode; int /*<<< orphan*/  io_pad_mode; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  dispc_lcd_enable_signal_polarity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_enable_fifohandcheck (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_enable_stallmode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_set_clock_div (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispc_mgr_set_io_pad_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_mgr_set_lcd_type_tft (int) ; 
 int /*<<< orphan*/  dispc_mgr_set_tft_data_lines (int,int /*<<< orphan*/ ) ; 

void dispc_mgr_set_lcd_config(enum omap_channel channel,
		const struct dss_lcd_mgr_config *config)
{
	dispc_mgr_set_io_pad_mode(config->io_pad_mode);

	dispc_mgr_enable_stallmode(channel, config->stallmode);
	dispc_mgr_enable_fifohandcheck(channel, config->fifohandcheck);

	dispc_mgr_set_clock_div(channel, &config->clock_info);

	dispc_mgr_set_tft_data_lines(channel, config->video_port_width);

	dispc_lcd_enable_signal_polarity(config->lcden_sig_polarity);

	dispc_mgr_set_lcd_type_tft(channel);
}