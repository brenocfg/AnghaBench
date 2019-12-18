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
struct buffer_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  internal_delete_pointers_items (struct buffer_info*,int,int,int) ; 

__attribute__((used)) static void internal_delete_childs(struct buffer_info *cur_bi, int from, int n)
{
	int i_from;

	i_from = (from == 0) ? from : from - 1;

	/*
	 * delete n pointers starting from `from' position in CUR;
	 * delete n keys starting from 'i_from' position in CUR;
	 */
	internal_delete_pointers_items(cur_bi, from, i_from, n);
}