#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gc_arena {int dummy; } ;
struct TYPE_3__ {int ping_rec_timeout_action; } ;
struct context {TYPE_2__* sig; TYPE_1__ options; } ;
struct TYPE_4__ {char* signal_text; int /*<<< orphan*/  signal_received; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_INFO ; 
#define  PING_EXIT 129 
#define  PING_RESTART 128 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  format_common_name (struct context*,struct gc_arena*) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
check_ping_restart_dowork(struct context *c)
{
    struct gc_arena gc = gc_new();
    switch (c->options.ping_rec_timeout_action)
    {
        case PING_EXIT:
            msg(M_INFO, "%sInactivity timeout (--ping-exit), exiting",
                format_common_name(c, &gc));
            c->sig->signal_received = SIGTERM;
            c->sig->signal_text = "ping-exit";
            break;

        case PING_RESTART:
            msg(M_INFO, "%sInactivity timeout (--ping-restart), restarting",
                format_common_name(c, &gc));
            c->sig->signal_received = SIGUSR1; /* SOFT-SIGUSR1 -- Ping Restart */
            c->sig->signal_text = "ping-restart";
            break;

        default:
            ASSERT(0);
    }
    gc_free(&gc);
}