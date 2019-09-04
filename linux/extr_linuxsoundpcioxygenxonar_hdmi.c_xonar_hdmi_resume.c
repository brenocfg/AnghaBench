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
struct xonar_hdmi {int dummy; } ;
struct oxygen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xonar_hdmi_init_commands (struct oxygen*,struct xonar_hdmi*) ; 

void xonar_hdmi_resume(struct oxygen *chip, struct xonar_hdmi *hdmi)
{
	xonar_hdmi_init_commands(chip, hdmi);
}