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
struct ds1343_priv {int /*<<< orphan*/  map; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  DS1343_TRICKLE_1K 131 
#define  DS1343_TRICKLE_2K 130 
#define  DS1343_TRICKLE_4K 129 
#define  DS1343_TRICKLE_DS1 128 
 int DS1343_TRICKLE_MAGIC ; 
 int /*<<< orphan*/  DS1343_TRICKLE_REG ; 
 struct ds1343_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

__attribute__((used)) static ssize_t ds1343_show_tricklecharger(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct ds1343_priv *priv = dev_get_drvdata(dev);
	int data;
	char *diodes = "disabled", *resistors = " ";

	regmap_read(priv->map, DS1343_TRICKLE_REG, &data);

	if ((data & 0xf0) == DS1343_TRICKLE_MAGIC) {
		switch (data & 0x0c) {
		case DS1343_TRICKLE_DS1:
			diodes = "one diode,";
			break;

		default:
			diodes = "no diode,";
			break;
		}

		switch (data & 0x03) {
		case DS1343_TRICKLE_1K:
			resistors = "1k Ohm";
			break;

		case DS1343_TRICKLE_2K:
			resistors = "2k Ohm";
			break;

		case DS1343_TRICKLE_4K:
			resistors = "4k Ohm";
			break;

		default:
			diodes = "disabled";
			break;
		}
	}

	return sprintf(buf, "%s %s\n", diodes, resistors);
}