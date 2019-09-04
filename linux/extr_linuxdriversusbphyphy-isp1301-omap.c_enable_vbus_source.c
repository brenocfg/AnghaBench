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
struct isp1301 {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void enable_vbus_source(struct isp1301 *isp)
{
	/* this board won't supply more than 8mA vbus power.
	 * some boards can switch a 100ma "unit load" (or more).
	 */
}