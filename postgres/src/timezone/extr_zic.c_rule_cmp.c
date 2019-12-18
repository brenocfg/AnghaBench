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
struct rule {scalar_t__ r_hiyear; scalar_t__ r_month; int r_dayofmonth; } ;

/* Variables and functions */

__attribute__((used)) static int
rule_cmp(struct rule const *a, struct rule const *b)
{
	if (!a)
		return -!!b;
	if (!b)
		return 1;
	if (a->r_hiyear != b->r_hiyear)
		return a->r_hiyear < b->r_hiyear ? -1 : 1;
	if (a->r_month - b->r_month != 0)
		return a->r_month - b->r_month;
	return a->r_dayofmonth - b->r_dayofmonth;
}