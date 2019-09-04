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
typedef  enum pin_config_param { ____Placeholder_pin_config_param } pin_config_param ;

/* Variables and functions */
 unsigned long pinconf_to_config_packed (int,unsigned int) ; 

__attribute__((used)) static void add_setting(unsigned long **setting, enum pin_config_param param,
			unsigned arg)
{
	**setting = pinconf_to_config_packed(param, arg);
	(*setting)++;
}