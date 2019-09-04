#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct omap_hdmi {int /*<<< orphan*/  wp_idlemode; TYPE_1__ wp; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_WP_SYSCONFIG ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hdmi_wp_audio_core_req_enable (TYPE_1__*,int) ; 
 int /*<<< orphan*/  hdmi_wp_audio_enable (TYPE_1__*,int) ; 

__attribute__((used)) static void hdmi_stop_audio_stream(struct omap_hdmi *hd)
{
	hdmi_wp_audio_core_req_enable(&hd->wp, false);
	hdmi_wp_audio_enable(&hd->wp, false);
	REG_FLD_MOD(hd->wp.base, HDMI_WP_SYSCONFIG, hd->wp_idlemode, 3, 2);
}