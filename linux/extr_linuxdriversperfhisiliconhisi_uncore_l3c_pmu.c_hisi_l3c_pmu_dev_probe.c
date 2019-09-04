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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hisi_pmu {int counter_bits; int on_cpu; int check_event; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * ops; int /*<<< orphan*/  num_counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  L3C_NR_COUNTERS ; 
 int hisi_l3c_pmu_init_data (struct platform_device*,struct hisi_pmu*) ; 
 int hisi_l3c_pmu_init_irq (struct hisi_pmu*,struct platform_device*) ; 
 int /*<<< orphan*/  hisi_uncore_l3c_ops ; 

__attribute__((used)) static int hisi_l3c_pmu_dev_probe(struct platform_device *pdev,
				  struct hisi_pmu *l3c_pmu)
{
	int ret;

	ret = hisi_l3c_pmu_init_data(pdev, l3c_pmu);
	if (ret)
		return ret;

	ret = hisi_l3c_pmu_init_irq(l3c_pmu, pdev);
	if (ret)
		return ret;

	l3c_pmu->num_counters = L3C_NR_COUNTERS;
	l3c_pmu->counter_bits = 48;
	l3c_pmu->ops = &hisi_uncore_l3c_ops;
	l3c_pmu->dev = &pdev->dev;
	l3c_pmu->on_cpu = -1;
	l3c_pmu->check_event = 0x59;

	return 0;
}