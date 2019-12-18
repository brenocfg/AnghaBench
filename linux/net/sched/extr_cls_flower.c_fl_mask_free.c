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
struct fl_flow_mask {int /*<<< orphan*/  ht; int /*<<< orphan*/  filters; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct fl_flow_mask*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fl_mask_free(struct fl_flow_mask *mask, bool mask_init_done)
{
	/* temporary masks don't have their filters list and ht initialized */
	if (mask_init_done) {
		WARN_ON(!list_empty(&mask->filters));
		rhashtable_destroy(&mask->ht);
	}
	kfree(mask);
}