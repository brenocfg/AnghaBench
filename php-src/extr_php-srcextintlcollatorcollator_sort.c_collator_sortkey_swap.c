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
typedef  int /*<<< orphan*/  collator_sort_key_index_t ;

/* Variables and functions */

__attribute__((used)) static void collator_sortkey_swap(collator_sort_key_index_t *p, collator_sort_key_index_t *q) /* {{{ */
{
	collator_sort_key_index_t t;
	t = *p;
	*p = *q;
	*q = t;
}