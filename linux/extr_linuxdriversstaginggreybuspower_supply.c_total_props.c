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
struct gb_power_supply {int properties_count; int properties_count_str; } ;

/* Variables and functions */

__attribute__((used)) static int total_props(struct gb_power_supply *gbpsy)
{
	/* this return the intval plus the strval properties */
	return (gbpsy->properties_count + gbpsy->properties_count_str);
}