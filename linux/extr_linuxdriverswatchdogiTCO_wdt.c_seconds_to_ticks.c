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
struct iTCO_wdt_private {int iTCO_version; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int seconds_to_ticks(struct iTCO_wdt_private *p,
					    int secs)
{
	return p->iTCO_version == 3 ? secs : (secs * 10) / 6;
}