#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct smc_pnetentry {int /*<<< orphan*/  ib_port; TYPE_3__* smcibdev; TYPE_1__* ndev; int /*<<< orphan*/  pnet_name; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ibdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_PNETID_ETHNAME ; 
 int /*<<< orphan*/  SMC_PNETID_IBNAME ; 
 int /*<<< orphan*/  SMC_PNETID_IBPORT ; 
 int /*<<< orphan*/  SMC_PNETID_NAME ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smc_pnet_set_nla(struct sk_buff *msg, struct smc_pnetentry *pnetelem)
{
	if (nla_put_string(msg, SMC_PNETID_NAME, pnetelem->pnet_name) ||
	    nla_put_string(msg, SMC_PNETID_ETHNAME, pnetelem->ndev->name) ||
	    nla_put_string(msg, SMC_PNETID_IBNAME,
			   pnetelem->smcibdev->ibdev->name) ||
	    nla_put_u8(msg, SMC_PNETID_IBPORT, pnetelem->ib_port))
		return -1;
	return 0;
}