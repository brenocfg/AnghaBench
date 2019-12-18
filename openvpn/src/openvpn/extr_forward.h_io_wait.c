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
struct TYPE_2__ {unsigned int event_set_status; scalar_t__ fast_io; } ;
struct context {TYPE_1__ c2; } ;

/* Variables and functions */
 unsigned int const IOW_MBUF ; 
 unsigned int const IOW_TO_LINK ; 
 unsigned int const IOW_TO_TUN ; 
 unsigned int SOCKET_WRITE ; 
 unsigned int TUN_WRITE ; 

__attribute__((used)) static inline void
io_wait(struct context *c, const unsigned int flags)
{
    void io_wait_dowork(struct context *c, const unsigned int flags);

    if (c->c2.fast_io && (flags & (IOW_TO_TUN|IOW_TO_LINK|IOW_MBUF)))
    {
        /* fast path -- only for TUN/TAP/UDP writes */
        unsigned int ret = 0;
        if (flags & IOW_TO_TUN)
        {
            ret |= TUN_WRITE;
        }
        if (flags & (IOW_TO_LINK|IOW_MBUF))
        {
            ret |= SOCKET_WRITE;
        }
        c->c2.event_set_status = ret;
    }
    else
    {
        /* slow path */
        io_wait_dowork(c, flags);
    }
}