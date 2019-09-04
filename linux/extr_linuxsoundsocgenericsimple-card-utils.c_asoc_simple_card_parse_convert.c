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
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct asoc_simple_card_data {int /*<<< orphan*/  convert_channels; int /*<<< orphan*/  convert_rate; } ;
typedef  int /*<<< orphan*/  prop ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

void asoc_simple_card_parse_convert(struct device *dev, char *prefix,
				    struct asoc_simple_card_data *data)
{
	struct device_node *np = dev->of_node;
	char prop[128];

	if (!prefix)
		prefix = "";

	/* sampling rate convert */
	snprintf(prop, sizeof(prop), "%s%s", prefix, "convert-rate");
	of_property_read_u32(np, prop, &data->convert_rate);

	/* channels transfer */
	snprintf(prop, sizeof(prop), "%s%s", prefix, "convert-channels");
	of_property_read_u32(np, prop, &data->convert_channels);

	dev_dbg(dev, "convert_rate     %d\n", data->convert_rate);
	dev_dbg(dev, "convert_channels %d\n", data->convert_channels);
}