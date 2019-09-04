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
struct rv3028_data {int /*<<< orphan*/  regmap; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  RV3028_EVT_CTRL ; 
 int /*<<< orphan*/  RV3028_EVT_CTRL_TSR ; 
 struct rv3028_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t timestamp0_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct rv3028_data *rv3028 = dev_get_drvdata(dev->parent);

	regmap_update_bits(rv3028->regmap, RV3028_EVT_CTRL, RV3028_EVT_CTRL_TSR,
			   RV3028_EVT_CTRL_TSR);

	return count;
}