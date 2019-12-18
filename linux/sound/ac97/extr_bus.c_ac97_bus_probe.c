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
struct device {int /*<<< orphan*/  driver; } ;
struct ac97_codec_driver {int (* probe ) (struct ac97_codec_device*) ;} ;
struct ac97_codec_device {int dummy; } ;

/* Variables and functions */
 int ac97_get_enable_clk (struct ac97_codec_device*) ; 
 int /*<<< orphan*/  ac97_put_disable_clk (struct ac97_codec_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int stub1 (struct ac97_codec_device*) ; 
 struct ac97_codec_device* to_ac97_device (struct device*) ; 
 struct ac97_codec_driver* to_ac97_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ac97_bus_probe(struct device *dev)
{
	struct ac97_codec_device *adev = to_ac97_device(dev);
	struct ac97_codec_driver *adrv = to_ac97_driver(dev->driver);
	int ret;

	ret = ac97_get_enable_clk(adev);
	if (ret)
		return ret;

	pm_runtime_get_noresume(dev);
	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);

	ret = adrv->probe(adev);
	if (ret == 0)
		return 0;

	pm_runtime_disable(dev);
	pm_runtime_set_suspended(dev);
	pm_runtime_put_noidle(dev);
	ac97_put_disable_clk(adev);

	return ret;
}