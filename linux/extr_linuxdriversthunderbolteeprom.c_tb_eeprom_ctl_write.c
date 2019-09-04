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
struct tb_switch {scalar_t__ cap_plug_events; } ;
struct tb_eeprom_ctl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_SWITCH ; 
 int tb_sw_write (struct tb_switch*,struct tb_eeprom_ctl*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int tb_eeprom_ctl_write(struct tb_switch *sw, struct tb_eeprom_ctl *ctl)
{
	return tb_sw_write(sw, ctl, TB_CFG_SWITCH, sw->cap_plug_events + 4, 1);
}