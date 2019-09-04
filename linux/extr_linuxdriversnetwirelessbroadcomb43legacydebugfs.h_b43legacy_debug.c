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
struct b43legacy_wldev {int dummy; } ;
typedef  enum b43legacy_dyndbg { ____Placeholder_b43legacy_dyndbg } b43legacy_dyndbg ;

/* Variables and functions */

__attribute__((used)) static inline
int b43legacy_debug(struct b43legacy_wldev *dev,
		    enum b43legacy_dyndbg feature)
{
	return 0;
}