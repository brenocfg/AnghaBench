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
struct regulator_dev {int dummy; } ;
struct isl_pmic {int /*<<< orphan*/  mtx; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct isl_pmic* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int isl6271a_get_voltage_sel(struct regulator_dev *dev)
{
	struct isl_pmic *pmic = rdev_get_drvdata(dev);
	int idx;

	mutex_lock(&pmic->mtx);

	idx = i2c_smbus_read_byte(pmic->client);
	if (idx < 0)
		dev_err(&pmic->client->dev, "Error getting voltage\n");

	mutex_unlock(&pmic->mtx);
	return idx;
}