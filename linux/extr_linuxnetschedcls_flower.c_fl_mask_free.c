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
struct fl_flow_mask {int /*<<< orphan*/  ht; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct fl_flow_mask*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fl_mask_free(struct fl_flow_mask *mask)
{
	rhashtable_destroy(&mask->ht);
	kfree(mask);
}