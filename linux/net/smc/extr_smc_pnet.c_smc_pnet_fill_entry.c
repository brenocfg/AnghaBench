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
struct smc_user_pnetentry {int ib_port; int /*<<< orphan*/  smcibdev; int /*<<< orphan*/  smcd_dev; int /*<<< orphan*/  ndev; int /*<<< orphan*/  pnet_name; int /*<<< orphan*/  list; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int SMC_MAX_PORTS ; 
 size_t SMC_PNETID_ETHNAME ; 
 size_t SMC_PNETID_IBNAME ; 
 size_t SMC_PNETID_IBPORT ; 
 size_t SMC_PNETID_NAME ; 
 int /*<<< orphan*/  dev_get_by_name (struct net*,char*) ; 
 struct net init_net ; 
 int /*<<< orphan*/  memset (struct smc_user_pnetentry*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nla_data (struct nlattr*) ; 
 int nla_get_u8 (struct nlattr*) ; 
 int /*<<< orphan*/  smc_pnet_find_ib (char*) ; 
 int /*<<< orphan*/  smc_pnet_find_smcd (char*) ; 
 int /*<<< orphan*/  smc_pnetid_valid (char*,int /*<<< orphan*/ ) ; 
 char* strim (char*) ; 

__attribute__((used)) static int smc_pnet_fill_entry(struct net *net,
			       struct smc_user_pnetentry *pnetelem,
			       struct nlattr *tb[])
{
	char *string, *ibname;
	int rc;

	memset(pnetelem, 0, sizeof(*pnetelem));
	INIT_LIST_HEAD(&pnetelem->list);

	rc = -EINVAL;
	if (!tb[SMC_PNETID_NAME])
		goto error;
	string = (char *)nla_data(tb[SMC_PNETID_NAME]);
	if (!smc_pnetid_valid(string, pnetelem->pnet_name))
		goto error;

	rc = -EINVAL;
	if (tb[SMC_PNETID_ETHNAME]) {
		string = (char *)nla_data(tb[SMC_PNETID_ETHNAME]);
		pnetelem->ndev = dev_get_by_name(net, string);
		if (!pnetelem->ndev)
			goto error;
	}

	/* if this is not the initial namespace, stop here */
	if (net != &init_net)
		return 0;

	rc = -EINVAL;
	if (tb[SMC_PNETID_IBNAME]) {
		ibname = (char *)nla_data(tb[SMC_PNETID_IBNAME]);
		ibname = strim(ibname);
		pnetelem->smcibdev = smc_pnet_find_ib(ibname);
		pnetelem->smcd_dev = smc_pnet_find_smcd(ibname);
		if (!pnetelem->smcibdev && !pnetelem->smcd_dev)
			goto error;
		if (pnetelem->smcibdev) {
			if (!tb[SMC_PNETID_IBPORT])
				goto error;
			pnetelem->ib_port = nla_get_u8(tb[SMC_PNETID_IBPORT]);
			if (pnetelem->ib_port < 1 ||
			    pnetelem->ib_port > SMC_MAX_PORTS)
				goto error;
		}
	}

	return 0;

error:
	return rc;
}