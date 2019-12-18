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
 scalar_t__ str_has_prefix (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static bool synth_field_signed(char *type)
{
	if (str_has_prefix(type, "u"))
		return false;
	if (strcmp(type, "gfp_t") == 0)
		return false;

	return true;
}