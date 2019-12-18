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
struct TYPE_5__ {int keycode; } ;
typedef  TYPE_2__ pending_key_t ;

/* Variables and functions */

void interpret_as_normal(pending_pair_t *p) {
    pending_key_t *k;
    k = p->down;
    if (k != NULL) {
        k->keycode = k->keycode & 0xFF;
    }
    k = p->up;
    if (k != NULL) {
        k->keycode = k->keycode & 0xFF;
    }
}