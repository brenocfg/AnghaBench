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
 unsigned short ARRAY_SIZE (char const**) ; 
 char const** mod_state_strings ; 

__attribute__((used)) static const char *mod_state_to_str(unsigned short mod_state)
{
	if (mod_state >= ARRAY_SIZE(mod_state_strings))
		return "Unknown module state";
	return mod_state_strings[mod_state];
}