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
struct TYPE_6__ {int /*<<< orphan*/  transport; int /*<<< orphan*/ * sasl_conn; scalar_t__ write_and_free; } ;
typedef  TYPE_1__ conn ;
struct TYPE_7__ {int /*<<< orphan*/  sasl; } ;

/* Variables and functions */
 scalar_t__ IS_UDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_read ; 
 int /*<<< orphan*/  conn_release_items (TYPE_1__*) ; 
 int /*<<< orphan*/  conn_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  sasl_dispose (int /*<<< orphan*/ **) ; 
 TYPE_2__ settings ; 

__attribute__((used)) static void conn_cleanup(conn *c) {
    assert(c != NULL);

    conn_release_items(c);

    if (c->write_and_free) {
        free(c->write_and_free);
        c->write_and_free = 0;
    }

    if (c->sasl_conn) {
        assert(settings.sasl);
        sasl_dispose(&c->sasl_conn);
        c->sasl_conn = NULL;
    }

    if (IS_UDP(c->transport)) {
        conn_set_state(c, conn_read);
    }
}