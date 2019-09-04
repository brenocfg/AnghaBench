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
struct gb_power_supply_get_supplies_response {scalar_t__ supplies_count; } ;
struct gb_power_supplies {scalar_t__ supplies_count; int /*<<< orphan*/  connection; } ;
typedef  int /*<<< orphan*/  resp ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GB_POWER_SUPPLY_TYPE_GET_SUPPLIES ; 
 int gb_operation_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gb_power_supply_get_supplies_response*,int) ; 

__attribute__((used)) static int gb_power_supplies_get_count(struct gb_power_supplies *supplies)
{
	struct gb_power_supply_get_supplies_response resp;
	int ret;

	ret = gb_operation_sync(supplies->connection,
				GB_POWER_SUPPLY_TYPE_GET_SUPPLIES,
				NULL, 0, &resp, sizeof(resp));
	if (ret < 0)
		return ret;

	if  (!resp.supplies_count)
		return -EINVAL;

	supplies->supplies_count = resp.supplies_count;

	return ret;
}