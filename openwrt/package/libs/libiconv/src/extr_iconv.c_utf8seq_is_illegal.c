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

__attribute__((used)) static inline int utf8seq_is_illegal(char *s, int n)
{
	return ((n == 3) && (*s == 0xEF) && (*(s+1) == 0xBF) &&
	        (*(s+2) >= 0xBE) && (*(s+2) <= 0xBF));
}