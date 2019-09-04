#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t mp_uint_t ;
struct TYPE_5__ {int /*<<< orphan*/  parent; TYPE_1__* methods; } ;
typedef  TYPE_2__ mp_irq_obj_t ;
struct TYPE_6__ {size_t len; scalar_t__* items; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* disable ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_3__ MP_STATE_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_irq_obj_list ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void mp_irq_disable_all (void) {
    // re-enable all active callback objects one by one
    for (mp_uint_t i = 0; i < MP_STATE_PORT(mp_irq_obj_list).len; i++) {
        mp_irq_obj_t *callback_obj = ((mp_irq_obj_t *)(MP_STATE_PORT(mp_irq_obj_list).items[i]));
        callback_obj->methods->disable(callback_obj->parent);
    }
}