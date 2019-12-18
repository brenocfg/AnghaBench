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
struct max9860_priv {int /*<<< orphan*/  dvddio; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 struct max9860_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max9860_remove(struct i2c_client *i2c)
{
	struct device *dev = &i2c->dev;
	struct max9860_priv *max9860 = dev_get_drvdata(dev);

	pm_runtime_disable(dev);
	regulator_disable(max9860->dvddio);
	return 0;
}