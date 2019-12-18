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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct mp_pin {scalar_t__ dir; int within_conn; int /*<<< orphan*/  manual_connection; struct mp_pin* conn; struct mp_pin* user_conn; struct mp_pin* other; TYPE_1__ data; int /*<<< orphan*/  data_requested; } ;

/* Variables and functions */
 scalar_t__ MP_PIN_IN ; 
 scalar_t__ MP_PIN_OUT ; 
 int /*<<< orphan*/  add_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct mp_pin* find_connected_end (struct mp_pin*) ; 

__attribute__((used)) static void init_connection(struct mp_pin *p)
{
    if (p->dir == MP_PIN_IN)
        p = p->other;

    struct mp_pin *in = find_connected_end(p);
    struct mp_pin *out = find_connected_end(p->other);

    // These are the "outer" pins by definition, they have no user connections.
    assert(!in->user_conn);
    assert(!out->user_conn);

    // Logicaly, the ends are always manual connections. A pin chain without
    // manual connections at the ends is still disconnected (or if this
    // attempted to extend an existing connection, becomes dangling and gets
    // disconnected).
    if (!in->manual_connection || !out->manual_connection)
        return;

    assert(in->dir == MP_PIN_IN);
    assert(out->dir == MP_PIN_OUT);

    struct mp_pin *cur = in;
    while (cur) {
        assert(!cur->within_conn && !cur->other->within_conn);
        assert(!cur->conn && !cur->other->conn);
        assert(!cur->data_requested); // unused for in pins
        assert(!cur->data.type); // unused for in pins
        assert(!cur->other->data_requested); // unset for unconnected out pins
        assert(!cur->other->data.type); // unset for unconnected out pins
        cur->within_conn = cur->other->within_conn = true;
        cur = cur->other->user_conn;
    }

    in->conn = out;
    in->within_conn = false;
    out->conn = in;
    out->within_conn = false;

    // Scheduling so far will be messed up.
    add_pending(in->manual_connection);
    add_pending(out->manual_connection);
}