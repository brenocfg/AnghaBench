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
struct TYPE_2__ {int capabilities; scalar_t__ ext_lfb_base; scalar_t__ lfb_base; } ;

/* Variables and functions */
 int VIDEO_CAPABILITY_64BIT_BASE ; 
 TYPE_1__ screen_info ; 

__attribute__((used)) static inline bool fb_base_is_valid(void)
{
	if (screen_info.lfb_base)
		return true;

	if (!(screen_info.capabilities & VIDEO_CAPABILITY_64BIT_BASE))
		return false;

	if (screen_info.ext_lfb_base)
		return true;

	return false;
}