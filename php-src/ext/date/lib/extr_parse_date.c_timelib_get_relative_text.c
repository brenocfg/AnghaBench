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
typedef  int /*<<< orphan*/  timelib_sll ;

/* Variables and functions */
 int /*<<< orphan*/  timelib_lookup_relative_text (char**,int*) ; 

__attribute__((used)) static timelib_sll timelib_get_relative_text(char **ptr, int *behavior)
{
	while (**ptr == ' ' || **ptr == '\t' || **ptr == '-' || **ptr == '/') {
		++*ptr;
	}
	return timelib_lookup_relative_text(ptr, behavior);
}