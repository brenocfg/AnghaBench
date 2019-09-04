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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 char* kmemdup (char const*,int,int /*<<< orphan*/ ) ; 
 int query_regdb (char const*) ; 
 TYPE_1__* reg_pdev ; 
 scalar_t__ regdb ; 
 int /*<<< orphan*/  regdb_fw_cb ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int query_regdb_file(const char *alpha2)
{
	ASSERT_RTNL();

	if (regdb)
		return query_regdb(alpha2);

	alpha2 = kmemdup(alpha2, 2, GFP_KERNEL);
	if (!alpha2)
		return -ENOMEM;

	return request_firmware_nowait(THIS_MODULE, true, "regulatory.db",
				       &reg_pdev->dev, GFP_KERNEL,
				       (void *)alpha2, regdb_fw_cb);
}