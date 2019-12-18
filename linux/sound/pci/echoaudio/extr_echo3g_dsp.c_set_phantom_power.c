#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct echoaudio {char phantom_power; TYPE_1__* comm_page; } ;
struct TYPE_2__ {int /*<<< orphan*/  e3g_frq_register; int /*<<< orphan*/  control_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  E3G_PHANTOM_POWER ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int write_control_reg (struct echoaudio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_phantom_power(struct echoaudio *chip, char on)
{
	u32 control_reg = le32_to_cpu(chip->comm_page->control_register);

	if (on)
		control_reg |= E3G_PHANTOM_POWER;
	else
		control_reg &= ~E3G_PHANTOM_POWER;

	chip->phantom_power = on;
	return write_control_reg(chip, control_reg,
				 le32_to_cpu(chip->comm_page->e3g_frq_register),
				 0);
}