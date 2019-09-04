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
struct smc_sock {int use_fallback; int fallback_rsn; TYPE_1__ sk; } ;

/* Variables and functions */
 scalar_t__ SMC_ACTIVE ; 
 scalar_t__ SMC_INIT ; 
 int /*<<< orphan*/  smc_copy_sock_settings_to_clc (struct smc_sock*) ; 

__attribute__((used)) static int smc_connect_fallback(struct smc_sock *smc, int reason_code)
{
	smc->use_fallback = true;
	smc->fallback_rsn = reason_code;
	smc_copy_sock_settings_to_clc(smc);
	if (smc->sk.sk_state == SMC_INIT)
		smc->sk.sk_state = SMC_ACTIVE;
	return 0;
}