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
struct abx500_chargalg {int /*<<< orphan*/  dev; int /*<<< orphan*/  chargalg_kobject; } ;

/* Variables and functions */
 int /*<<< orphan*/  abx500_chargalg_ktype ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int abx500_chargalg_sysfs_init(struct abx500_chargalg *di)
{
	int ret = 0;

	ret = kobject_init_and_add(&di->chargalg_kobject,
		&abx500_chargalg_ktype,
		NULL, "abx500_chargalg");
	if (ret < 0)
		dev_err(di->dev, "failed to create sysfs entry\n");

	return ret;
}