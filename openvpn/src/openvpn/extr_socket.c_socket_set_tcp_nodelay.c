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
typedef  int /*<<< orphan*/  state ;

/* Variables and functions */
 int /*<<< orphan*/  D_OSBUF ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  M_WARN ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static bool
socket_set_tcp_nodelay(int sd, int state)
{
#if defined(_WIN32) || (defined(HAVE_SETSOCKOPT) && defined(IPPROTO_TCP) && defined(TCP_NODELAY))
    if (setsockopt(sd, IPPROTO_TCP, TCP_NODELAY, (void *) &state, sizeof(state)) != 0)
    {
        msg(M_WARN, "NOTE: setsockopt TCP_NODELAY=%d failed", state);
        return false;
    }
    else
    {
        dmsg(D_OSBUF, "Socket flags: TCP_NODELAY=%d succeeded", state);
        return true;
    }
#else  /* if defined(_WIN32) || (defined(HAVE_SETSOCKOPT) && defined(IPPROTO_TCP) && defined(TCP_NODELAY)) */
    msg(M_WARN, "NOTE: setsockopt TCP_NODELAY=%d failed (No kernel support)", state);
    return false;
#endif
}