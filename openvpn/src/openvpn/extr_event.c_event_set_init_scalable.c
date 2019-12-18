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
struct event_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct event_set*) ; 
 int /*<<< orphan*/  M_WARN ; 
 struct event_set* ep_init (int*,unsigned int) ; 
 struct event_set* event_set_init_simple (int*,unsigned int) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct event_set *
event_set_init_scalable(int *maxevents, unsigned int flags)
{
    struct event_set *ret = NULL;
#if EPOLL
    ret = ep_init(maxevents, flags);
    if (!ret)
    {
        msg(M_WARN, "Note: sys_epoll API is unavailable, falling back to poll/select API");
        ret = event_set_init_simple(maxevents, flags);
    }
#else  /* if EPOLL */
    ret = event_set_init_simple(maxevents, flags);
#endif
    ASSERT(ret);
    return ret;
}