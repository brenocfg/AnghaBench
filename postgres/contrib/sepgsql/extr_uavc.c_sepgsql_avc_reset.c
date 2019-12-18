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
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int AVC_NUM_SLOTS ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 scalar_t__ avc_lru_hint ; 
 int /*<<< orphan*/  avc_mem_cxt ; 
 scalar_t__ avc_num_caches ; 
 int /*<<< orphan*/  avc_slots ; 
 int /*<<< orphan*/ * avc_unlabeled ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sepgsql_avc_reset(void)
{
	MemoryContextReset(avc_mem_cxt);

	memset(avc_slots, 0, sizeof(List *) * AVC_NUM_SLOTS);
	avc_num_caches = 0;
	avc_lru_hint = 0;
	avc_unlabeled = NULL;
}