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
typedef  int /*<<< orphan*/  u32 ;
struct rt9455_info {int /*<<< orphan*/  boost_voltage; int /*<<< orphan*/  voreg; TYPE_1__* client; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int device_property_read_u32 (struct device*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rt9455_discover_charger(struct rt9455_info *info, u32 *ichrg,
				   u32 *ieoc_percentage,
				   u32 *mivr, u32 *iaicr)
{
	struct device *dev = &info->client->dev;
	int ret;

	if (!dev->of_node && !ACPI_HANDLE(dev)) {
		dev_err(dev, "No support for either device tree or ACPI\n");
		return -EINVAL;
	}
	/*
	 * ICHRG, IEOC_PERCENTAGE, VOREG and boost output voltage are mandatory
	 * parameters.
	 */
	ret = device_property_read_u32(dev, "richtek,output-charge-current",
				       ichrg);
	if (ret) {
		dev_err(dev, "Error: missing \"output-charge-current\" property\n");
		return ret;
	}

	ret = device_property_read_u32(dev, "richtek,end-of-charge-percentage",
				       ieoc_percentage);
	if (ret) {
		dev_err(dev, "Error: missing \"end-of-charge-percentage\" property\n");
		return ret;
	}

	ret = device_property_read_u32(dev,
				       "richtek,battery-regulation-voltage",
				       &info->voreg);
	if (ret) {
		dev_err(dev, "Error: missing \"battery-regulation-voltage\" property\n");
		return ret;
	}

	ret = device_property_read_u32(dev, "richtek,boost-output-voltage",
				       &info->boost_voltage);
	if (ret) {
		dev_err(dev, "Error: missing \"boost-output-voltage\" property\n");
		return ret;
	}

	/*
	 * MIVR and IAICR are optional parameters. Do not return error if one of
	 * them is not present in ACPI table or device tree specification.
	 */
	device_property_read_u32(dev, "richtek,min-input-voltage-regulation",
				 mivr);
	device_property_read_u32(dev, "richtek,avg-input-current-regulation",
				 iaicr);

	return 0;
}