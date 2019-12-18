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
struct TYPE_2__ {int /*<<< orphan*/  proto; } ;
struct options {scalar_t__ ping_rec_timeout_action; int /*<<< orphan*/  ping_rec_timeout; TYPE_1__ ce; scalar_t__ pull; } ;

/* Variables and functions */
 scalar_t__ PING_RESTART ; 
 scalar_t__ PING_UNDEF ; 
 int /*<<< orphan*/  PRE_PULL_INITIAL_PING_RESTART ; 
 scalar_t__ proto_is_dgram (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_options_ce_post(struct options *options)
{
#if P2MP
    /*
     * In pull mode, we usually import --ping/--ping-restart parameters from
     * the server.  However we should also set an initial default --ping-restart
     * for the period of time before we pull the --ping-restart parameter
     * from the server.
     */
    if (options->pull
        && options->ping_rec_timeout_action == PING_UNDEF
        && proto_is_dgram(options->ce.proto))
    {
        options->ping_rec_timeout = PRE_PULL_INITIAL_PING_RESTART;
        options->ping_rec_timeout_action = PING_RESTART;
    }
#endif
}