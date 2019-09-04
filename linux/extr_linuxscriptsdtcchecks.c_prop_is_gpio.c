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
struct property {char* name; } ;

/* Variables and functions */
 scalar_t__ streq (char*,char*) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static bool prop_is_gpio(struct property *prop)
{
	char *str;

	/*
	 * *-gpios and *-gpio can appear in property names,
	 * so skip over any false matches (only one known ATM)
	 */
	if (strstr(prop->name, "nr-gpio"))
		return false;

	str = strrchr(prop->name, '-');
	if (str)
		str++;
	else
		str = prop->name;
	if (!(streq(str, "gpios") || streq(str, "gpio")))
		return false;

	return true;
}