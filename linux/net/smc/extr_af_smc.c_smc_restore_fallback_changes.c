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
struct TYPE_4__ {int /*<<< orphan*/  sk_socket; } ;
struct smc_sock {TYPE_3__* clcsock; TYPE_1__ sk; } ;
struct TYPE_6__ {TYPE_2__* file; } ;
struct TYPE_5__ {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */

__attribute__((used)) static void smc_restore_fallback_changes(struct smc_sock *smc)
{
	smc->clcsock->file->private_data = smc->sk.sk_socket;
	smc->clcsock->file = NULL;
}