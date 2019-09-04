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
struct chain_allocator {int safe_needed; int /*<<< orphan*/  gfp_mask; int /*<<< orphan*/  used_space; int /*<<< orphan*/ * chain; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  LINKED_PAGE_DATA_SIZE ; 

__attribute__((used)) static void chain_init(struct chain_allocator *ca, gfp_t gfp_mask,
		       int safe_needed)
{
	ca->chain = NULL;
	ca->used_space = LINKED_PAGE_DATA_SIZE;
	ca->gfp_mask = gfp_mask;
	ca->safe_needed = safe_needed;
}