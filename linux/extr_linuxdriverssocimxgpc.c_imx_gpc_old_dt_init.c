#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* power_on ) (TYPE_1__*) ;} ;
struct imx_pm_domain {int ipg_rate_mhz; TYPE_1__ base; int /*<<< orphan*/  supply; struct regmap* regmap; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PM_GENERIC_DOMAINS ; 
 size_t GPC_PGC_DOMAIN_PU ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,char*) ; 
 struct imx_pm_domain* imx_gpc_domains ; 
 int /*<<< orphan*/  imx_gpc_onecell_data ; 
 int imx_pgc_get_clocks (struct device*,struct imx_pm_domain*) ; 
 int /*<<< orphan*/  imx_pgc_put_clocks (struct imx_pm_domain*) ; 
 int of_genpd_add_provider_onecell (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_genpd_init (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_genpd_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static int imx_gpc_old_dt_init(struct device *dev, struct regmap *regmap,
			       unsigned int num_domains)
{
	struct imx_pm_domain *domain;
	int i, ret;

	for (i = 0; i < num_domains; i++) {
		domain = &imx_gpc_domains[i];
		domain->regmap = regmap;
		domain->ipg_rate_mhz = 66;

		if (i == 1) {
			domain->supply = devm_regulator_get(dev, "pu");
			if (IS_ERR(domain->supply))
				return PTR_ERR(domain->supply);

			ret = imx_pgc_get_clocks(dev, domain);
			if (ret)
				goto clk_err;

			domain->base.power_on(&domain->base);
		}
	}

	for (i = 0; i < num_domains; i++)
		pm_genpd_init(&imx_gpc_domains[i].base, NULL, false);

	if (IS_ENABLED(CONFIG_PM_GENERIC_DOMAINS)) {
		ret = of_genpd_add_provider_onecell(dev->of_node,
						    &imx_gpc_onecell_data);
		if (ret)
			goto genpd_err;
	}

	return 0;

genpd_err:
	for (i = 0; i < num_domains; i++)
		pm_genpd_remove(&imx_gpc_domains[i].base);
	imx_pgc_put_clocks(&imx_gpc_domains[GPC_PGC_DOMAIN_PU]);
clk_err:
	return ret;
}