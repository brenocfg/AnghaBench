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
 int strspn (char const*,char*) ; 

__attribute__((used)) static int
integer_digits(const char *my_str)
{
	/* ignoring any sign ... */
	if (my_str[0] == '-' || my_str[0] == '+')
		my_str++;
	/* ... count initial integral digits */
	return strspn(my_str, "0123456789");
}