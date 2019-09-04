#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ obs_weak_encoder_t ;
struct TYPE_7__ {TYPE_1__* control; } ;
typedef  TYPE_2__ obs_encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_encoder_destroy (TYPE_2__*) ; 
 scalar_t__ obs_ref_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_weak_encoder_release (TYPE_1__*) ; 

void obs_encoder_release(obs_encoder_t *encoder)
{
	if (!encoder)
		return;

	obs_weak_encoder_t *control = encoder->control;
	if (obs_ref_release(&control->ref)) {
		// The order of operations is important here since
		// get_context_by_name in obs.c relies on weak refs
		// being alive while the context is listed
		obs_encoder_destroy(encoder);
		obs_weak_encoder_release(control);
	}
}