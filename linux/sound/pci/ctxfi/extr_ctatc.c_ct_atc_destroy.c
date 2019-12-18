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
struct ct_atc {int /*<<< orphan*/ * vm; scalar_t__ hw; scalar_t__* rsc_mgrs; scalar_t__ mixer; int /*<<< orphan*/ * timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (scalar_t__) ;} ;

/* Variables and functions */
 int NUM_RSCTYP ; 
 int /*<<< orphan*/  atc_release_resources (struct ct_atc*) ; 
 int /*<<< orphan*/  ct_mixer_destroy (scalar_t__) ; 
 int /*<<< orphan*/  ct_timer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ct_vm_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_hw_obj (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ct_atc*) ; 
 TYPE_1__* rsc_mgr_funcs ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static int ct_atc_destroy(struct ct_atc *atc)
{
	int i = 0;

	if (!atc)
		return 0;

	if (atc->timer) {
		ct_timer_free(atc->timer);
		atc->timer = NULL;
	}

	atc_release_resources(atc);

	/* Destroy internal mixer objects */
	if (atc->mixer)
		ct_mixer_destroy(atc->mixer);

	for (i = 0; i < NUM_RSCTYP; i++) {
		if (rsc_mgr_funcs[i].destroy && atc->rsc_mgrs[i])
			rsc_mgr_funcs[i].destroy(atc->rsc_mgrs[i]);

	}

	if (atc->hw)
		destroy_hw_obj(atc->hw);

	/* Destroy device virtual memory manager object */
	if (atc->vm) {
		ct_vm_destroy(atc->vm);
		atc->vm = NULL;
	}

	kfree(atc);

	return 0;
}