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
 scalar_t__ spacetab (char) ; 

__attribute__((used)) static inline char *next_terminator(char *first, const char *last)
{
	for (; first <= last; first++)
		if (spacetab(*first) || !*first)
			return first;
	return NULL;
}