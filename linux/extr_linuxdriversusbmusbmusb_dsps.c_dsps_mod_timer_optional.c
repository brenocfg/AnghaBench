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
struct dsps_glue {scalar_t__ vbus_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsps_mod_timer (struct dsps_glue*,int) ; 

__attribute__((used)) static void dsps_mod_timer_optional(struct dsps_glue *glue)
{
	if (glue->vbus_irq)
		return;

	dsps_mod_timer(glue, -1);
}