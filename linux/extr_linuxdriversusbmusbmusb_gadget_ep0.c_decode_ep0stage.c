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
typedef  int u8 ;

/* Variables and functions */
#define  MUSB_EP0_STAGE_ACKWAIT 134 
#define  MUSB_EP0_STAGE_IDLE 133 
#define  MUSB_EP0_STAGE_RX 132 
#define  MUSB_EP0_STAGE_SETUP 131 
#define  MUSB_EP0_STAGE_STATUSIN 130 
#define  MUSB_EP0_STAGE_STATUSOUT 129 
#define  MUSB_EP0_STAGE_TX 128 

__attribute__((used)) static char *decode_ep0stage(u8 stage)
{
	switch (stage) {
	case MUSB_EP0_STAGE_IDLE:	return "idle";
	case MUSB_EP0_STAGE_SETUP:	return "setup";
	case MUSB_EP0_STAGE_TX:		return "in";
	case MUSB_EP0_STAGE_RX:		return "out";
	case MUSB_EP0_STAGE_ACKWAIT:	return "wait";
	case MUSB_EP0_STAGE_STATUSIN:	return "in/status";
	case MUSB_EP0_STAGE_STATUSOUT:	return "out/status";
	default:			return "?";
	}
}