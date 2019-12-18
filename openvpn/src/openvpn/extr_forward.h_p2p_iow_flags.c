#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ len; } ;
struct TYPE_4__ {scalar_t__ len; } ;
struct TYPE_6__ {TYPE_2__ to_tun; TYPE_1__ to_link; } ;
struct context {TYPE_3__ c2; } ;

/* Variables and functions */
 unsigned int IOW_CHECK_RESIDUAL ; 
 unsigned int IOW_FRAG ; 
 unsigned int IOW_READ ; 
 unsigned int IOW_SHAPER ; 
 unsigned int IOW_TO_LINK ; 
 unsigned int IOW_TO_TUN ; 
 unsigned int IOW_WAIT_SIGNAL ; 

__attribute__((used)) static inline unsigned int
p2p_iow_flags(const struct context *c)
{
    unsigned int flags = (IOW_SHAPER|IOW_CHECK_RESIDUAL|IOW_FRAG|IOW_READ|IOW_WAIT_SIGNAL);
    if (c->c2.to_link.len > 0)
    {
        flags |= IOW_TO_LINK;
    }
    if (c->c2.to_tun.len > 0)
    {
        flags |= IOW_TO_TUN;
    }
    return flags;
}