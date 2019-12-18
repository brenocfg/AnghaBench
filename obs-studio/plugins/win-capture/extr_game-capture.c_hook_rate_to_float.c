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
typedef  enum hook_rate { ____Placeholder_hook_rate } hook_rate ;

/* Variables and functions */
#define  HOOK_RATE_FAST 131 
#define  HOOK_RATE_FASTEST 130 
#define  HOOK_RATE_NORMAL 129 
#define  HOOK_RATE_SLOW 128 

__attribute__((used)) static inline float hook_rate_to_float(enum hook_rate rate)
{
	switch (rate) {
	case HOOK_RATE_SLOW:
		return 2.0f;
	case HOOK_RATE_FAST:
		return 0.5f;
	case HOOK_RATE_FASTEST:
		return 0.1f;
	case HOOK_RATE_NORMAL:
		/* FALLTHROUGH */
	default:
		return 1.0f;
	}
}