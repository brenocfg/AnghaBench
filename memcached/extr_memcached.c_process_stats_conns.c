#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ state; int /*<<< orphan*/  last_cmd_time; int /*<<< orphan*/  transport; } ;
typedef  int /*<<< orphan*/  ADD_STAT ;

/* Variables and functions */
 int /*<<< orphan*/  APPEND_NUM_STAT (int,char*,char*,...) ; 
 scalar_t__ IS_UDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int STAT_KEY_LEN ; 
 int STAT_VAL_LEN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ conn_closed ; 
 scalar_t__ conn_listening ; 
 scalar_t__ conn_read ; 
 int /*<<< orphan*/  conn_to_str (TYPE_1__*,char*,char*) ; 
 TYPE_1__** conns ; 
 int /*<<< orphan*/  current_time ; 
 int max_fds ; 
 int state_text (scalar_t__) ; 

__attribute__((used)) static void process_stats_conns(ADD_STAT add_stats, void *c) {
    int i;
    char key_str[STAT_KEY_LEN];
    char val_str[STAT_VAL_LEN];
    size_t extras_len = sizeof("unix:") + sizeof("65535");
    char addr[MAXPATHLEN + extras_len];
    char svr_addr[MAXPATHLEN + extras_len];
    int klen = 0, vlen = 0;

    assert(add_stats);

    for (i = 0; i < max_fds; i++) {
        if (conns[i]) {
            /* This is safe to do unlocked because conns are never freed; the
             * worst that'll happen will be a minor inconsistency in the
             * output -- not worth the complexity of the locking that'd be
             * required to prevent it.
             */
            if (IS_UDP(conns[i]->transport)) {
                APPEND_NUM_STAT(i, "UDP", "%s", "UDP");
            }
            if (conns[i]->state != conn_closed) {
                conn_to_str(conns[i], addr, svr_addr);

                APPEND_NUM_STAT(i, "addr", "%s", addr);
                if (conns[i]->state != conn_listening &&
                    !(IS_UDP(conns[i]->transport) && conns[i]->state == conn_read)) {
                    APPEND_NUM_STAT(i, "listen_addr", "%s", svr_addr);
                }
                APPEND_NUM_STAT(i, "state", "%s",
                        state_text(conns[i]->state));
                APPEND_NUM_STAT(i, "secs_since_last_cmd", "%d",
                        current_time - conns[i]->last_cmd_time);
            }
        }
    }
}