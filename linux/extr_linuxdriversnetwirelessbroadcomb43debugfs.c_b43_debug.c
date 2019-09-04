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
struct b43_wldev {TYPE_1__* dfsentry; } ;
typedef  enum b43_dyndbg { ____Placeholder_b43_dyndbg } b43_dyndbg ;
struct TYPE_2__ {scalar_t__* dyn_debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_VERBOSITY_MAX ; 
 int /*<<< orphan*/  b43_modparam_verbose ; 
 scalar_t__ unlikely (int) ; 

bool b43_debug(struct b43_wldev *dev, enum b43_dyndbg feature)
{
	bool enabled;

	enabled = (dev->dfsentry && dev->dfsentry->dyn_debug[feature]);
	if (unlikely(enabled)) {
		/* Force full debugging messages, if the user enabled
		 * some dynamic debugging feature. */
		b43_modparam_verbose = B43_VERBOSITY_MAX;
	}

	return enabled;
}