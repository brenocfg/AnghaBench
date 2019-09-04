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
struct smcd_dev {int dummy; } ;
struct smc_sock {TYPE_1__* clcsock; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int SMC_CLC_DECL_CNFERR ; 
 int /*<<< orphan*/  smc_pnet_find_ism_resource (int /*<<< orphan*/ ,struct smcd_dev**) ; 

__attribute__((used)) static int smc_check_ism(struct smc_sock *smc, struct smcd_dev **ismdev)
{
	/* Find ISM device with same PNETID as connecting interface  */
	smc_pnet_find_ism_resource(smc->clcsock->sk, ismdev);
	if (!(*ismdev))
		return SMC_CLC_DECL_CNFERR; /* configuration error */
	return 0;
}