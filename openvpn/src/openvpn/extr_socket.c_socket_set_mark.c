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
typedef  int /*<<< orphan*/  mark ;

/* Variables and functions */
 int /*<<< orphan*/  M_WARN ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_MARK ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static inline void
socket_set_mark(int sd, int mark)
{
#if defined(TARGET_LINUX) && HAVE_DECL_SO_MARK
    if (mark && setsockopt(sd, SOL_SOCKET, SO_MARK, (void *) &mark, sizeof(mark)) != 0)
    {
        msg(M_WARN, "NOTE: setsockopt SO_MARK=%d failed", mark);
    }
#endif
}