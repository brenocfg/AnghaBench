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
struct options {int server_flags; scalar_t__ mode; int /*<<< orphan*/  sockflags; int /*<<< orphan*/  gc; } ;

/* Variables and functions */
 scalar_t__ MODE_SERVER ; 
 int /*<<< orphan*/  M_USAGE ; 
 int /*<<< orphan*/  SF_TCP_NODELAY ; 
 int SF_TCP_NODELAY_HELPER ; 
 int /*<<< orphan*/  print_str (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_option (struct options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
helper_tcp_nodelay(struct options *o)
{
#if P2MP_SERVER
    if (o->server_flags & SF_TCP_NODELAY_HELPER)
    {
        if (o->mode == MODE_SERVER)
        {
            o->sockflags |= SF_TCP_NODELAY;
            push_option(o, print_str("socket-flags TCP_NODELAY", &o->gc), M_USAGE);
        }
        else
        {
            o->sockflags |= SF_TCP_NODELAY;
        }
    }
#endif
}