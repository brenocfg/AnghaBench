#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_7__ {int /*<<< orphan*/  sfd; struct TYPE_7__* next; } ;
typedef  TYPE_1__ conn ;
struct TYPE_10__ {int /*<<< orphan*/  backlog; } ;
struct TYPE_9__ {int /*<<< orphan*/  listen_disabled_num; struct timeval maxconns_entered; int /*<<< orphan*/  time_in_listen_disabled_us; } ;
struct TYPE_8__ {int accepting_conns; } ;

/* Variables and functions */
 int EV_PERSIST ; 
 int EV_READ ; 
 int /*<<< orphan*/  STATS_LOCK () ; 
 int /*<<< orphan*/  STATS_UNLOCK () ; 
 int allow_new_conns ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ listen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* listen_conn ; 
 int /*<<< orphan*/  maxconns_handler (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 TYPE_5__ settings ; 
 TYPE_4__ stats ; 
 TYPE_3__ stats_state ; 
 int /*<<< orphan*/  update_event (TYPE_1__*,int) ; 

void do_accept_new_conns(const bool do_accept) {
    conn *next;

    for (next = listen_conn; next; next = next->next) {
        if (do_accept) {
            update_event(next, EV_READ | EV_PERSIST);
            if (listen(next->sfd, settings.backlog) != 0) {
                perror("listen");
            }
        }
        else {
            update_event(next, 0);
            if (listen(next->sfd, 0) != 0) {
                perror("listen");
            }
        }
    }

    if (do_accept) {
        struct timeval maxconns_exited;
        uint64_t elapsed_us;
        gettimeofday(&maxconns_exited,NULL);
        STATS_LOCK();
        elapsed_us =
            (maxconns_exited.tv_sec - stats.maxconns_entered.tv_sec) * 1000000
            + (maxconns_exited.tv_usec - stats.maxconns_entered.tv_usec);
        stats.time_in_listen_disabled_us += elapsed_us;
        stats_state.accepting_conns = true;
        STATS_UNLOCK();
    } else {
        STATS_LOCK();
        stats_state.accepting_conns = false;
        gettimeofday(&stats.maxconns_entered,NULL);
        stats.listen_disabled_num++;
        STATS_UNLOCK();
        allow_new_conns = false;
        maxconns_handler(-42, 0, 0);
    }
}