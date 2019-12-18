#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* up; TYPE_2__* down; } ;
typedef  TYPE_1__ pending_pair_t ;
struct TYPE_10__ {struct TYPE_10__* next; } ;
typedef  TYPE_2__ pending_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  is_down (TYPE_2__*) ; 
 scalar_t__ is_up (TYPE_2__*) ; 
 scalar_t__ keys_match (TYPE_2__*,TYPE_2__*) ; 

bool is_downup_pair(pending_key_t *k, pending_pair_t *p) {
    // first, make sure this event is keydown.
    if (!is_down(k)) {
        return false;
    }
    // now find its matching keyup.
    pending_key_t *next = k->next;
    while (next != NULL) {
        if (keys_match(k, next) && is_up(next)) {
            // found it.
            if (p != NULL) {
                p->down = k;
                p->up = next;
            }
            return true;
        }
        next = next->next;
    }
    // didn't find it.
    return false;
}