#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omap_hdmi {int /*<<< orphan*/  wp; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {TYPE_1__ wp; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_WP_SYSCONFIG ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 TYPE_2__ hdmi ; 
 int /*<<< orphan*/  hdmi_wp_audio_core_req_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hdmi_wp_audio_enable (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hdmi_start_audio_stream(struct omap_hdmi *hd)
{
	REG_FLD_MOD(hdmi.wp.base, HDMI_WP_SYSCONFIG, 1, 3, 2);
	hdmi_wp_audio_enable(&hd->wp, true);
	hdmi_wp_audio_core_req_enable(&hd->wp, true);
}