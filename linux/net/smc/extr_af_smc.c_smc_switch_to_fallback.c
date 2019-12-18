#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* sk_socket; } ;
struct smc_sock {int use_fallback; TYPE_4__* clcsock; TYPE_3__ sk; } ;
struct TYPE_8__ {TYPE_1__* file; } ;
struct TYPE_6__ {TYPE_1__* file; } ;
struct TYPE_5__ {TYPE_4__* private_data; } ;

/* Variables and functions */

__attribute__((used)) static void smc_switch_to_fallback(struct smc_sock *smc)
{
	smc->use_fallback = true;
	if (smc->sk.sk_socket && smc->sk.sk_socket->file) {
		smc->clcsock->file = smc->sk.sk_socket->file;
		smc->clcsock->file->private_data = smc->clcsock;
	}
}