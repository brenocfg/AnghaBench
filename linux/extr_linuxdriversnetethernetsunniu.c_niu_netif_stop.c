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
struct niu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_trans_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  niu_disable_napi (struct niu*) ; 

__attribute__((used)) static void niu_netif_stop(struct niu *np)
{
	netif_trans_update(np->dev);	/* prevent tx timeout */

	niu_disable_napi(np);

	netif_tx_disable(np->dev);
}