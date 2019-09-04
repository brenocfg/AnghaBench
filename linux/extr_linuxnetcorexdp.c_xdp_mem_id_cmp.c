#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ id; } ;
struct xdp_mem_allocator {TYPE_1__ mem; } ;
struct rhashtable_compare_arg {scalar_t__ key; } ;

/* Variables and functions */

__attribute__((used)) static int xdp_mem_id_cmp(struct rhashtable_compare_arg *arg,
			  const void *ptr)
{
	const struct xdp_mem_allocator *xa = ptr;
	u32 mem_id = *(u32 *)arg->key;

	return xa->mem.id != mem_id;
}