#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* up; TYPE_2__* down; } ;
typedef  TYPE_1__ pending_pair_t ;
struct TYPE_5__ {void* keycode; } ;
typedef  TYPE_2__ pending_key_t ;

/* Variables and functions */
 void* get_mod_kc (void*) ; 

void interpret_as_mod(pending_pair_t *p) {
    // see https://github.com/qmk/qmk_firmware/issues/1503
    pending_key_t *k;
    k = p->down;
    if (k != NULL) {
        k->keycode = get_mod_kc(k->keycode);
    }
    k = p->up;
    if (k != NULL) {
        k->keycode = get_mod_kc(k->keycode);
    }
}