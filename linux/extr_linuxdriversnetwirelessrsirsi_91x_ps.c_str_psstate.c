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
typedef  enum ps_state { ____Placeholder_ps_state } ps_state ;

/* Variables and functions */
#define  PS_DISABLE_REQ_SENT 131 
#define  PS_ENABLED 130 
#define  PS_ENABLE_REQ_SENT 129 
#define  PS_NONE 128 

char *str_psstate(enum ps_state state)
{
	switch (state) {
	case PS_NONE:
		return "PS_NONE";
	case PS_DISABLE_REQ_SENT:
		return "PS_DISABLE_REQ_SENT";
	case PS_ENABLE_REQ_SENT:
		return "PS_ENABLE_REQ_SENT";
	case PS_ENABLED:
		return "PS_ENABLED";
	default:
		return "INVALID_STATE";
	}
}