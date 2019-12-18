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
typedef  enum conn_states { ____Placeholder_conn_states } conn_states ;
struct TYPE_4__ {int state; int sfd; int /*<<< orphan*/  wbytes; int /*<<< orphan*/  wbuf; } ;
typedef  TYPE_1__ conn ;
struct TYPE_5__ {int verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCACHED_PROCESS_COMMAND_END (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int conn_listening ; 
 int conn_max_state ; 
 int conn_mwrite ; 
 int conn_write ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*,char*) ; 
 TYPE_2__ settings ; 
 char* state_text (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void conn_set_state(conn *c, enum conn_states state) {
    assert(c != NULL);
    assert(state >= conn_listening && state < conn_max_state);

    if (state != c->state) {
        if (settings.verbose > 2) {
            fprintf(stderr, "%d: going from %s to %s\n",
                    c->sfd, state_text(c->state),
                    state_text(state));
        }

        if (state == conn_write || state == conn_mwrite) {
            MEMCACHED_PROCESS_COMMAND_END(c->sfd, c->wbuf, c->wbytes);
        }
        c->state = state;
    }
}