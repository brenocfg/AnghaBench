#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  power_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  control_type ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* platform_rapl_domain ; 
 int /*<<< orphan*/  powercap_unregister_control_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powercap_unregister_zone (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rapl_unregister_powercap(void)
{
	if (platform_rapl_domain) {
		powercap_unregister_zone(control_type,
					 &platform_rapl_domain->power_zone);
		kfree(platform_rapl_domain);
	}
	powercap_unregister_control_type(control_type);
}