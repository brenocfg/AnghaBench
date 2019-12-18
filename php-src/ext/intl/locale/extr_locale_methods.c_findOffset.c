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
typedef  int int16_t ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char const* const) ; 

__attribute__((used)) static int16_t findOffset(const char* const* list, const char* key)
{
	const char* const* anchor = list;
	while (*list != NULL) {
		if (strcmp(key, *list) == 0) {
			return (int16_t)(list - anchor);
		}
		list++;
	}

	return -1;

}