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
struct dmi_system_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHT_SURFACE_MACH ; 
 int /*<<< orphan*/  cht_machine_id ; 

__attribute__((used)) static int cht_surface_quirk_cb(const struct dmi_system_id *id)
{
	cht_machine_id = CHT_SURFACE_MACH;
	return 1;
}