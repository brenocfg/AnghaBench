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
struct i2c_child_t {int dummy; } ;
struct TYPE_2__ {unsigned char* mon_type; } ;

/* Variables and functions */
 int ENVCTRL_MAX_CPU ; 
 int PCF8584_MAX_CHANNELS ; 
 TYPE_1__* i2c_childlist ; 

__attribute__((used)) static struct i2c_child_t *envctrl_get_i2c_child(unsigned char mon_type)
{
	int i, j;

	for (i = 0; i < ENVCTRL_MAX_CPU*2; i++) {
		for (j = 0; j < PCF8584_MAX_CHANNELS; j++) {
			if (i2c_childlist[i].mon_type[j] == mon_type) {
				return (struct i2c_child_t *)(&(i2c_childlist[i]));
			}
		}
	}
	return NULL;
}