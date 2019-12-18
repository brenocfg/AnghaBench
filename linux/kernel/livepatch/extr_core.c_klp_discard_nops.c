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
struct klp_patch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  klp_free_objects_dynamic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  klp_transition_patch ; 
 int /*<<< orphan*/  klp_unpatch_objects_dynamic (int /*<<< orphan*/ ) ; 

void klp_discard_nops(struct klp_patch *new_patch)
{
	klp_unpatch_objects_dynamic(klp_transition_patch);
	klp_free_objects_dynamic(klp_transition_patch);
}