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
typedef  enum gr_ep0state { ____Placeholder_gr_ep0state } gr_ep0state ;

/* Variables and functions */
 int ARRAY_SIZE (char const* const*) ; 
#define  GR_EP0_DISCONNECT 135 
#define  GR_EP0_IDATA 134 
#define  GR_EP0_ISTATUS 133 
#define  GR_EP0_ODATA 132 
#define  GR_EP0_OSTATUS 131 
#define  GR_EP0_SETUP 130 
#define  GR_EP0_STALL 129 
#define  GR_EP0_SUSPEND 128 

__attribute__((used)) static const char *gr_ep0state_string(enum gr_ep0state state)
{
	static const char *const names[] = {
		[GR_EP0_DISCONNECT] = "disconnect",
		[GR_EP0_SETUP] = "setup",
		[GR_EP0_IDATA] = "idata",
		[GR_EP0_ODATA] = "odata",
		[GR_EP0_ISTATUS] = "istatus",
		[GR_EP0_OSTATUS] = "ostatus",
		[GR_EP0_STALL] = "stall",
		[GR_EP0_SUSPEND] = "suspend",
	};

	if (state < 0 || state >= ARRAY_SIZE(names))
		return "UNKNOWN";

	return names[state];
}