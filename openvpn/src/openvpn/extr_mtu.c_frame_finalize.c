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
struct frame {int link_mtu; int link_mtu_dynamic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  M_FATAL ; 
 int /*<<< orphan*/  M_WARN ; 
 int TUN_LINK_DELTA (struct frame*) ; 
 scalar_t__ TUN_MTU_MIN ; 
 scalar_t__ TUN_MTU_SIZE (struct frame*) ; 
 int /*<<< orphan*/  frame_print (struct frame*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

void
frame_finalize(struct frame *frame,
               bool link_mtu_defined,
               int link_mtu,
               bool tun_mtu_defined,
               int tun_mtu)
{
    /* Set link_mtu based on command line options */
    if (tun_mtu_defined)
    {
        ASSERT(!link_mtu_defined);
        frame->link_mtu = tun_mtu + TUN_LINK_DELTA(frame);
    }
    else
    {
        ASSERT(link_mtu_defined);
        frame->link_mtu = link_mtu;
    }

    if (TUN_MTU_SIZE(frame) < TUN_MTU_MIN)
    {
        msg(M_WARN, "TUN MTU value (%d) must be at least %d", TUN_MTU_SIZE(frame), TUN_MTU_MIN);
        frame_print(frame, M_FATAL, "MTU is too small");
    }

    frame->link_mtu_dynamic = frame->link_mtu;
}