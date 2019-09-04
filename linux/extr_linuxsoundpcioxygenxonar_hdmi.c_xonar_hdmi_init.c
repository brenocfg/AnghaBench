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
struct xonar_hdmi {int* params; } ;
struct oxygen {int dummy; } ;

/* Variables and functions */
 int IEC958_AES3_CON_FS_48000 ; 
 int /*<<< orphan*/  xonar_hdmi_init_commands (struct oxygen*,struct xonar_hdmi*) ; 

void xonar_hdmi_init(struct oxygen *chip, struct xonar_hdmi *hdmi)
{
	hdmi->params[1] = IEC958_AES3_CON_FS_48000;
	hdmi->params[4] = 1;
	xonar_hdmi_init_commands(chip, hdmi);
}