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
struct TYPE_2__ {scalar_t__ type; } ;
struct mp_pin {scalar_t__ dir; int within_conn; int data_requested; struct mp_pin* user_conn; struct mp_pin* other; TYPE_1__ data; int /*<<< orphan*/  owner; int /*<<< orphan*/ * conn; } ;

/* Variables and functions */
 scalar_t__ MP_PIN_OUT ; 
 int /*<<< orphan*/  MP_VERBOSE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct mp_pin* find_connected_end (struct mp_pin*) ; 
 int /*<<< orphan*/  mp_frame_unref (TYPE_1__*) ; 

__attribute__((used)) static void deinit_connection(struct mp_pin *p)
{
    if (p->dir == MP_PIN_OUT)
        p = p->other;

    p = find_connected_end(p);

    while (p) {
        p->conn = p->other->conn = NULL;
        p->within_conn = p->other->within_conn = false;
        assert(!p->other->data_requested); // unused for in pins
        assert(!p->other->data.type); // unused for in pins
        p->data_requested = false;
        if (p->data.type)
            MP_VERBOSE(p->owner, "dropping frame due to pin disconnect\n");
        if (p->data_requested)
            MP_VERBOSE(p->owner, "dropping request due to pin disconnect\n");
        mp_frame_unref(&p->data);
        p = p->other->user_conn;
    }
}