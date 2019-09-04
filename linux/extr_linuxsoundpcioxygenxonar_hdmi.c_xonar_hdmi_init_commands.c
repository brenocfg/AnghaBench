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
typedef  int u8 ;
struct xonar_hdmi {int* params; } ;
struct oxygen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdmi_write_command (struct oxygen*,int,int,int*) ; 
 int /*<<< orphan*/  oxygen_reset_uart (struct oxygen*) ; 

__attribute__((used)) static void xonar_hdmi_init_commands(struct oxygen *chip,
				     struct xonar_hdmi *hdmi)
{
	u8 param;

	oxygen_reset_uart(chip);
	param = 0;
	hdmi_write_command(chip, 0x61, 1, &param);
	param = 1;
	hdmi_write_command(chip, 0x74, 1, &param);
	hdmi_write_command(chip, 0x54, 5, hdmi->params);
}