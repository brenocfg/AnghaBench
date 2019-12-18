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
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static inline int newline_size(const char *array)
{
	if (strncmp(array, "\r\n", 2) == 0 || strncmp(array, "\n\r", 2) == 0)
		return 2;
	else if (*array == '\r' || *array == '\n')
		return 1;

	return 0;
}