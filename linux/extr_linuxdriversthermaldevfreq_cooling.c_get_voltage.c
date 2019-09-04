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
struct device {int dummy; } ;
struct TYPE_2__ {struct device* parent; } ;
struct devfreq {TYPE_1__ dev; } ;
struct dev_pm_opp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERANGE ; 
 scalar_t__ IS_ERR (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  PTR_ERR (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  dev_err_ratelimited (struct device*,char*,unsigned long,...) ; 
 struct dev_pm_opp* dev_pm_opp_find_freq_exact (struct device*,unsigned long,int) ; 
 int dev_pm_opp_get_voltage (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 

__attribute__((used)) static unsigned long get_voltage(struct devfreq *df, unsigned long freq)
{
	struct device *dev = df->dev.parent;
	unsigned long voltage;
	struct dev_pm_opp *opp;

	opp = dev_pm_opp_find_freq_exact(dev, freq, true);
	if (PTR_ERR(opp) == -ERANGE)
		opp = dev_pm_opp_find_freq_exact(dev, freq, false);

	if (IS_ERR(opp)) {
		dev_err_ratelimited(dev, "Failed to find OPP for frequency %lu: %ld\n",
				    freq, PTR_ERR(opp));
		return 0;
	}

	voltage = dev_pm_opp_get_voltage(opp) / 1000; /* mV */
	dev_pm_opp_put(opp);

	if (voltage == 0) {
		dev_err_ratelimited(dev,
				    "Failed to get voltage for frequency %lu\n",
				    freq);
	}

	return voltage;
}