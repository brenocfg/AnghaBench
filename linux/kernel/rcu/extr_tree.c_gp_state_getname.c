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

/* Variables and functions */
 short ARRAY_SIZE (char const**) ; 
 char const** gp_state_names ; 

__attribute__((used)) static const char *gp_state_getname(short gs)
{
	if (gs < 0 || gs >= ARRAY_SIZE(gp_state_names))
		return "???";
	return gp_state_names[gs];
}