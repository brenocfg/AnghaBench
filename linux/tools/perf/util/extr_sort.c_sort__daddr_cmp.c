#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct hist_entry {TYPE_2__* mem_info; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {scalar_t__ addr; } ;
struct TYPE_4__ {TYPE_1__ daddr; } ;

/* Variables and functions */

int64_t
sort__daddr_cmp(struct hist_entry *left, struct hist_entry *right)
{
	uint64_t l = 0, r = 0;

	if (left->mem_info)
		l = left->mem_info->daddr.addr;
	if (right->mem_info)
		r = right->mem_info->daddr.addr;

	return (int64_t)(r - l);
}