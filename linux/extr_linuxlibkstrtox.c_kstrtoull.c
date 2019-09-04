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
 int _kstrtoull (char const*,unsigned int,unsigned long long*) ; 

int kstrtoull(const char *s, unsigned int base, unsigned long long *res)
{
	if (s[0] == '+')
		s++;
	return _kstrtoull(s, base, res);
}