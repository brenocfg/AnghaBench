#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct smc_user_pnetentry {char* pnet_name; int ib_port; TYPE_4__* smcd_dev; TYPE_3__* smcibdev; TYPE_5__* ndev; } ;
struct sk_buff {int dummy; } ;
struct TYPE_10__ {char* name; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {TYPE_2__* ibdev; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_7__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_PNETID_ETHNAME ; 
 int /*<<< orphan*/  SMC_PNETID_IBNAME ; 
 int /*<<< orphan*/  SMC_PNETID_IBPORT ; 
 int /*<<< orphan*/  SMC_PNETID_NAME ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smc_pnet_set_nla(struct sk_buff *msg,
			    struct smc_user_pnetentry *pnetelem)
{
	if (nla_put_string(msg, SMC_PNETID_NAME, pnetelem->pnet_name))
		return -1;
	if (pnetelem->ndev) {
		if (nla_put_string(msg, SMC_PNETID_ETHNAME,
				   pnetelem->ndev->name))
			return -1;
	} else {
		if (nla_put_string(msg, SMC_PNETID_ETHNAME, "n/a"))
			return -1;
	}
	if (pnetelem->smcibdev) {
		if (nla_put_string(msg, SMC_PNETID_IBNAME,
			dev_name(pnetelem->smcibdev->ibdev->dev.parent)) ||
		    nla_put_u8(msg, SMC_PNETID_IBPORT, pnetelem->ib_port))
			return -1;
	} else if (pnetelem->smcd_dev) {
		if (nla_put_string(msg, SMC_PNETID_IBNAME,
				   dev_name(&pnetelem->smcd_dev->dev)) ||
		    nla_put_u8(msg, SMC_PNETID_IBPORT, 1))
			return -1;
	} else {
		if (nla_put_string(msg, SMC_PNETID_IBNAME, "n/a") ||
		    nla_put_u8(msg, SMC_PNETID_IBPORT, 0xff))
			return -1;
	}

	return 0;
}