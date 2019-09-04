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
struct gb_power_supplies {int /*<<< orphan*/  connection; } ;
struct gb_bundle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _gb_power_supplies_release (struct gb_power_supplies*) ; 
 int /*<<< orphan*/  gb_connection_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_disable (int /*<<< orphan*/ ) ; 
 struct gb_power_supplies* greybus_get_drvdata (struct gb_bundle*) ; 

__attribute__((used)) static void gb_power_supply_disconnect(struct gb_bundle *bundle)
{
	struct gb_power_supplies *supplies = greybus_get_drvdata(bundle);

	gb_connection_disable(supplies->connection);
	gb_connection_destroy(supplies->connection);

	_gb_power_supplies_release(supplies);
}