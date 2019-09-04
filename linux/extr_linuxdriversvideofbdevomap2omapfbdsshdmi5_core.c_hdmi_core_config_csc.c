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
struct hdmi_core_data {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_CORE_CSC_SCALE ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void hdmi_core_config_csc(struct hdmi_core_data *core)
{
	int clr_depth = 0;	/* 24 bit color depth */

	/* CSC_COLORDEPTH */
	REG_FLD_MOD(core->base, HDMI_CORE_CSC_SCALE, clr_depth, 7, 4);
}