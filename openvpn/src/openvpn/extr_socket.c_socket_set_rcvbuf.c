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
typedef  int /*<<< orphan*/  size ;

/* Variables and functions */
 int /*<<< orphan*/  M_WARN ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static bool
socket_set_rcvbuf(int sd, int size)
{
#if defined(HAVE_SETSOCKOPT) && defined(SOL_SOCKET) && defined(SO_RCVBUF)
    if (setsockopt(sd, SOL_SOCKET, SO_RCVBUF, (void *) &size, sizeof(size)) != 0)
    {
        msg(M_WARN, "NOTE: setsockopt SO_RCVBUF=%d failed", size);
        return false;
    }
    return true;
#endif
}