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
struct frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_MTU_UPPER_BOUND ; 
 scalar_t__ datagram_overhead (int) ; 
 int /*<<< orphan*/  frame_set_mtu_dynamic (struct frame*,scalar_t__,int /*<<< orphan*/ ) ; 

void
frame_adjust_path_mtu(struct frame *frame, int pmtu, int proto)
{
    frame_set_mtu_dynamic(frame, pmtu - datagram_overhead(proto), SET_MTU_UPPER_BOUND);
}