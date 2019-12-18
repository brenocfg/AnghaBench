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
struct wcd9335_codec {struct device* dev; } ;
struct device {int dummy; } ;
struct slim_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct wcd9335_codec*) ; 
 struct wcd9335_codec* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int wcd9335_parse_dt (struct wcd9335_codec*) ; 
 int wcd9335_power_on_reset (struct wcd9335_codec*) ; 

__attribute__((used)) static int wcd9335_slim_probe(struct slim_device *slim)
{
	struct device *dev = &slim->dev;
	struct wcd9335_codec *wcd;
	int ret;

	wcd = devm_kzalloc(dev, sizeof(*wcd), GFP_KERNEL);
	if (!wcd)
		return	-ENOMEM;

	wcd->dev = dev;
	ret = wcd9335_parse_dt(wcd);
	if (ret) {
		dev_err(dev, "Error parsing DT: %d\n", ret);
		return ret;
	}

	ret = wcd9335_power_on_reset(wcd);
	if (ret)
		return ret;

	dev_set_drvdata(dev, wcd);

	return 0;
}