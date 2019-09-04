#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_10__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ token_t ;
struct TYPE_11__ {int /*<<< orphan*/  event; int /*<<< orphan*/  sfd; } ;
typedef  TYPE_2__ conn ;

/* Variables and functions */
 int COMMAND_TOKEN ; 
#define  LOGGER_ADD_WATCHER_FAILED 130 
#define  LOGGER_ADD_WATCHER_OK 129 
#define  LOGGER_ADD_WATCHER_TOO_MANY 128 
 int /*<<< orphan*/  LOG_EVICTIONS ; 
 int /*<<< orphan*/  LOG_FETCHERS ; 
 int /*<<< orphan*/  LOG_MUTATIONS ; 
 int /*<<< orphan*/  LOG_RAWCMDS ; 
 int /*<<< orphan*/  LOG_SYSEVENTS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_set_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn_watch ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int logger_add_watcher (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_string (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  set_noreply_maybe (TYPE_2__*,TYPE_1__*,size_t const) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void process_watch_command(conn *c, token_t *tokens, const size_t ntokens) {
    uint16_t f = 0;
    int x;
    assert(c != NULL);

    set_noreply_maybe(c, tokens, ntokens);
    if (ntokens > 2) {
        for (x = COMMAND_TOKEN + 1; x < ntokens - 1; x++) {
            if ((strcmp(tokens[x].value, "rawcmds") == 0)) {
                f |= LOG_RAWCMDS;
            } else if ((strcmp(tokens[x].value, "evictions") == 0)) {
                f |= LOG_EVICTIONS;
            } else if ((strcmp(tokens[x].value, "fetchers") == 0)) {
                f |= LOG_FETCHERS;
            } else if ((strcmp(tokens[x].value, "mutations") == 0)) {
                f |= LOG_MUTATIONS;
            } else if ((strcmp(tokens[x].value, "sysevents") == 0)) {
                f |= LOG_SYSEVENTS;
            } else {
                out_string(c, "ERROR");
                return;
            }
        }
    } else {
        f |= LOG_FETCHERS;
    }

    switch(logger_add_watcher(c, c->sfd, f)) {
        case LOGGER_ADD_WATCHER_TOO_MANY:
            out_string(c, "WATCHER_TOO_MANY log watcher limit reached");
            break;
        case LOGGER_ADD_WATCHER_FAILED:
            out_string(c, "WATCHER_FAILED failed to add log watcher");
            break;
        case LOGGER_ADD_WATCHER_OK:
            conn_set_state(c, conn_watch);
            event_del(&c->event);
            break;
    }
}