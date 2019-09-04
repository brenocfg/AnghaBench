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
struct smc_sock {int /*<<< orphan*/  sk; TYPE_1__* clcsock; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  SK_FLAGS_SMC_TO_CLC ; 
 int /*<<< orphan*/  smc_copy_sock_settings (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smc_copy_sock_settings_to_clc(struct smc_sock *smc)
{
	smc_copy_sock_settings(smc->clcsock->sk, &smc->sk, SK_FLAGS_SMC_TO_CLC);
}