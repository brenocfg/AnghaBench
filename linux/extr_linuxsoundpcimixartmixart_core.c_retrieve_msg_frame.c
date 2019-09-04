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
typedef  scalar_t__ u32 ;
struct mixart_mgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIXART_MEM (struct mixart_mgr*,scalar_t__) ; 
 scalar_t__ MSG_BOUND_STACK_SIZE ; 
 scalar_t__ MSG_OUTBOUND_POST_HEAD ; 
 scalar_t__ MSG_OUTBOUND_POST_STACK ; 
 scalar_t__ MSG_OUTBOUND_POST_TAIL ; 
 scalar_t__ readl_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_be (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int retrieve_msg_frame(struct mixart_mgr *mgr, u32 *msg_frame)
{
	/* read the message frame fifo */
	u32 headptr, tailptr;

	tailptr = readl_be(MIXART_MEM(mgr, MSG_OUTBOUND_POST_TAIL));
	headptr = readl_be(MIXART_MEM(mgr, MSG_OUTBOUND_POST_HEAD));

	if (tailptr == headptr)
		return 0; /* no message posted */

	if (tailptr < MSG_OUTBOUND_POST_STACK)
		return 0; /* error */
	if (tailptr >= MSG_OUTBOUND_POST_STACK + MSG_BOUND_STACK_SIZE)
		return 0; /* error */

	*msg_frame = readl_be(MIXART_MEM(mgr, tailptr));

	/* increment the tail index */
	tailptr += 4;
	if( tailptr >= (MSG_OUTBOUND_POST_STACK+MSG_BOUND_STACK_SIZE) )
		tailptr = MSG_OUTBOUND_POST_STACK;
	writel_be(tailptr, MIXART_MEM(mgr, MSG_OUTBOUND_POST_TAIL));

	return 1;
}