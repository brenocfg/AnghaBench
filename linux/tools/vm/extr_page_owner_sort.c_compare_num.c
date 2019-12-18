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
struct block_list {int num; } ;

/* Variables and functions */

__attribute__((used)) static int compare_num(const void *p1, const void *p2)
{
	const struct block_list *l1 = p1, *l2 = p2;

	return l2->num - l1->num;
}