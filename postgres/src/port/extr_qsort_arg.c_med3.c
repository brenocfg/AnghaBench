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
typedef  scalar_t__ (* qsort_arg_comparator ) (char*,char*,void*) ;

/* Variables and functions */

__attribute__((used)) static char *
med3(char *a, char *b, char *c, qsort_arg_comparator cmp, void *arg)
{
	return cmp(a, b, arg) < 0 ?
		(cmp(b, c, arg) < 0 ? b : (cmp(a, c, arg) < 0 ? c : a))
		: (cmp(b, c, arg) > 0 ? b : (cmp(a, c, arg) < 0 ? a : c));
}