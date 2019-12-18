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
struct TYPE_2__ {int module_id; int instance_id; } ;
struct skl_module_pin {int pin_state; scalar_t__ is_dynamic; scalar_t__ in_use; TYPE_1__ id; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int MOD_BUF ; 
 scalar_t__ snprintf (char*,int,char*,char*,int,int,int,char*,char*,int,int) ; 

__attribute__((used)) static ssize_t skl_print_pins(struct skl_module_pin *m_pin, char *buf,
				int max_pin, ssize_t size, bool direction)
{
	int i;
	ssize_t ret = 0;

	for (i = 0; i < max_pin; i++)
		ret += snprintf(buf + size, MOD_BUF - size,
				"%s %d\n\tModule %d\n\tInstance %d\n\t"
				"In-used %s\n\tType %s\n"
				"\tState %d\n\tIndex %d\n",
				direction ? "Input Pin:" : "Output Pin:",
				i, m_pin[i].id.module_id,
				m_pin[i].id.instance_id,
				m_pin[i].in_use ? "Used" : "Unused",
				m_pin[i].is_dynamic ? "Dynamic" : "Static",
				m_pin[i].pin_state, i);
	return ret;
}