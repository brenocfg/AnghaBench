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
struct TYPE_2__ {scalar_t__ ncp_enabled; int /*<<< orphan*/  route_nopull; } ;
struct context {TYPE_1__ options; } ;

/* Variables and functions */
 unsigned int OPT_P_COMP ; 
 unsigned int OPT_P_ECHO ; 
 unsigned int OPT_P_EXPLICIT_NOTIFY ; 
 unsigned int OPT_P_IPWIN32 ; 
 unsigned int OPT_P_MESSAGES ; 
 unsigned int OPT_P_NCP ; 
 unsigned int OPT_P_PEER_ID ; 
 unsigned int OPT_P_PERSIST ; 
 unsigned int OPT_P_PULL_MODE ; 
 unsigned int OPT_P_ROUTE ; 
 unsigned int OPT_P_ROUTE_EXTRAS ; 
 unsigned int OPT_P_SETENV ; 
 unsigned int OPT_P_SHAPER ; 
 unsigned int OPT_P_SOCKBUF ; 
 unsigned int OPT_P_SOCKFLAGS ; 
 unsigned int OPT_P_TIMER ; 
 unsigned int OPT_P_UP ; 

unsigned int
pull_permission_mask(const struct context *c)
{
    unsigned int flags =
        OPT_P_UP
        | OPT_P_ROUTE_EXTRAS
        | OPT_P_SOCKBUF
        | OPT_P_SOCKFLAGS
        | OPT_P_SETENV
        | OPT_P_SHAPER
        | OPT_P_TIMER
        | OPT_P_COMP
        | OPT_P_PERSIST
        | OPT_P_MESSAGES
        | OPT_P_EXPLICIT_NOTIFY
        | OPT_P_ECHO
        | OPT_P_PULL_MODE
        | OPT_P_PEER_ID;

    if (!c->options.route_nopull)
    {
        flags |= (OPT_P_ROUTE | OPT_P_IPWIN32);
    }

    if (c->options.ncp_enabled)
    {
        flags |= OPT_P_NCP;
    }

    return flags;
}