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
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static bool synth_field_signed(char *type)
{
	if (strncmp(type, "u", 1) == 0)
		return false;

	return true;
}