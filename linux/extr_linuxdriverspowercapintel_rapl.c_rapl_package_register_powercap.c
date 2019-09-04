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
struct rapl_package {int nr_domains; int id; struct rapl_domain* domains; struct powercap_zone* power_zone; } ;
struct rapl_domain {size_t id; char* name; int /*<<< orphan*/  power_zone; } ;
struct powercap_zone {int dummy; } ;
typedef  int /*<<< orphan*/  dev_name ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct powercap_zone*) ; 
 int PTR_ERR (struct powercap_zone*) ; 
 size_t RAPL_DOMAIN_PACKAGE ; 
 int /*<<< orphan*/  constraint_ops ; 
 int /*<<< orphan*/  control_type ; 
 int find_nr_power_limit (struct rapl_domain*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 struct powercap_zone* powercap_register_zone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct powercap_zone*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  powercap_unregister_zone (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rapl_update_domain_data (struct rapl_package*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/ * zone_ops ; 

__attribute__((used)) static int rapl_package_register_powercap(struct rapl_package *rp)
{
	struct rapl_domain *rd;
	char dev_name[17]; /* max domain name = 7 + 1 + 8 for int + 1 for null*/
	struct powercap_zone *power_zone = NULL;
	int nr_pl, ret;

	/* Update the domain data of the new package */
	rapl_update_domain_data(rp);

	/* first we register package domain as the parent zone*/
	for (rd = rp->domains; rd < rp->domains + rp->nr_domains; rd++) {
		if (rd->id == RAPL_DOMAIN_PACKAGE) {
			nr_pl = find_nr_power_limit(rd);
			pr_debug("register socket %d package domain %s\n",
				rp->id, rd->name);
			memset(dev_name, 0, sizeof(dev_name));
			snprintf(dev_name, sizeof(dev_name), "%s-%d",
				rd->name, rp->id);
			power_zone = powercap_register_zone(&rd->power_zone,
							control_type,
							dev_name, NULL,
							&zone_ops[rd->id],
							nr_pl,
							&constraint_ops);
			if (IS_ERR(power_zone)) {
				pr_debug("failed to register package, %d\n",
					rp->id);
				return PTR_ERR(power_zone);
			}
			/* track parent zone in per package/socket data */
			rp->power_zone = power_zone;
			/* done, only one package domain per socket */
			break;
		}
	}
	if (!power_zone) {
		pr_err("no package domain found, unknown topology!\n");
		return -ENODEV;
	}
	/* now register domains as children of the socket/package*/
	for (rd = rp->domains; rd < rp->domains + rp->nr_domains; rd++) {
		if (rd->id == RAPL_DOMAIN_PACKAGE)
			continue;
		/* number of power limits per domain varies */
		nr_pl = find_nr_power_limit(rd);
		power_zone = powercap_register_zone(&rd->power_zone,
						control_type, rd->name,
						rp->power_zone,
						&zone_ops[rd->id], nr_pl,
						&constraint_ops);

		if (IS_ERR(power_zone)) {
			pr_debug("failed to register power_zone, %d:%s:%s\n",
				rp->id, rd->name, dev_name);
			ret = PTR_ERR(power_zone);
			goto err_cleanup;
		}
	}
	return 0;

err_cleanup:
	/*
	 * Clean up previously initialized domains within the package if we
	 * failed after the first domain setup.
	 */
	while (--rd >= rp->domains) {
		pr_debug("unregister package %d domain %s\n", rp->id, rd->name);
		powercap_unregister_zone(control_type, &rd->power_zone);
	}

	return ret;
}