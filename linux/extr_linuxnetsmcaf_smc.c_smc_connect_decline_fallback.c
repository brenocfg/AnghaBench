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
struct TYPE_2__ {scalar_t__ sk_state; } ;
struct smc_sock {TYPE_1__ sk; } ;

/* Variables and functions */
 int SMC_CLC_DECL_PEERDECL ; 
 scalar_t__ SMC_INIT ; 
 int smc_clc_send_decline (struct smc_sock*,int) ; 
 int smc_connect_fallback (struct smc_sock*,int) ; 
 int /*<<< orphan*/  sock_put (TYPE_1__*) ; 

__attribute__((used)) static int smc_connect_decline_fallback(struct smc_sock *smc, int reason_code)
{
	int rc;

	if (reason_code < 0) { /* error, fallback is not possible */
		if (smc->sk.sk_state == SMC_INIT)
			sock_put(&smc->sk); /* passive closing */
		return reason_code;
	}
	if (reason_code != SMC_CLC_DECL_PEERDECL) {
		rc = smc_clc_send_decline(smc, reason_code);
		if (rc < 0) {
			if (smc->sk.sk_state == SMC_INIT)
				sock_put(&smc->sk); /* passive closing */
			return rc;
		}
	}
	return smc_connect_fallback(smc, reason_code);
}