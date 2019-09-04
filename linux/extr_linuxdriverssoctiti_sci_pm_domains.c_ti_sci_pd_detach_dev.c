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
struct ti_sci_genpd_dev_data {int dummy; } ;
struct generic_pm_domain_data {struct ti_sci_genpd_dev_data* data; } ;
struct generic_pm_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct generic_pm_domain_data* dev_gpd_data (struct device*) ; 
 int /*<<< orphan*/  kfree (struct ti_sci_genpd_dev_data*) ; 

__attribute__((used)) static void ti_sci_pd_detach_dev(struct generic_pm_domain *domain,
				 struct device *dev)
{
	struct generic_pm_domain_data *genpd_data = dev_gpd_data(dev);
	struct ti_sci_genpd_dev_data *sci_dev_data = genpd_data->data;

	kfree(sci_dev_data);
	genpd_data->data = NULL;
}