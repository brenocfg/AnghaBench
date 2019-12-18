#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct options {int keepalive_ping; int keepalive_timeout; int ping_send_timeout; int ping_rec_timeout; scalar_t__ mode; int /*<<< orphan*/  gc; void* ping_rec_timeout_action; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ MODE_POINT_TO_POINT ; 
 scalar_t__ MODE_SERVER ; 
 int /*<<< orphan*/  M_USAGE ; 
 void* PING_RESTART ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_str_int (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_option (struct options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
helper_keepalive(struct options *o)
{
    if (o->keepalive_ping || o->keepalive_timeout)
    {
        /*
         * Sanity checks.
         */
        if (o->keepalive_ping <= 0 || o->keepalive_timeout <= 0)
        {
            msg(M_USAGE, "--keepalive parameters must be > 0");
        }
        if (o->keepalive_ping * 2 > o->keepalive_timeout)
        {
            msg(M_USAGE, "the second parameter to --keepalive (restart timeout=%d) must be at least twice the value of the first parameter (ping interval=%d).  A ratio of 1:5 or 1:6 would be even better.  Recommended setting is --keepalive 10 60.",
                o->keepalive_timeout,
                o->keepalive_ping);
        }
        if (o->ping_send_timeout || o->ping_rec_timeout)
        {
            msg(M_USAGE, "--keepalive conflicts with --ping, --ping-exit, or --ping-restart.  If you use --keepalive, you don't need any of the other --ping directives.");
        }

        /*
         * Expand.
         */
        if (o->mode == MODE_POINT_TO_POINT)
        {
            o->ping_rec_timeout_action = PING_RESTART;
            o->ping_send_timeout = o->keepalive_ping;
            o->ping_rec_timeout = o->keepalive_timeout;
        }
#if P2MP_SERVER
        else if (o->mode == MODE_SERVER)
        {
            o->ping_rec_timeout_action = PING_RESTART;
            o->ping_send_timeout = o->keepalive_ping;
            o->ping_rec_timeout = o->keepalive_timeout * 2;
            push_option(o, print_str_int("ping", o->keepalive_ping, &o->gc), M_USAGE);
            push_option(o, print_str_int("ping-restart", o->keepalive_timeout, &o->gc), M_USAGE);
        }
#endif
        else
        {
            ASSERT(0);
        }
    }
}