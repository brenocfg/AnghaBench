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
struct wilc {TYPE_1__** vif; int /*<<< orphan*/ * firmware; } ;
struct TYPE_2__ {scalar_t__ ndev; scalar_t__ mac_opened; } ;

/* Variables and functions */
 int NUM_CONCURRENT_IFC ; 
 int /*<<< orphan*/  free_netdev (scalar_t__) ; 
 int /*<<< orphan*/  g_dev_notifier ; 
 int /*<<< orphan*/  kfree (struct wilc*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_inetaddr_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (scalar_t__) ; 
 int /*<<< orphan*/  wilc_free_wiphy (scalar_t__) ; 
 int /*<<< orphan*/  wilc_mac_close (scalar_t__) ; 

void wilc_netdev_cleanup(struct wilc *wilc)
{
	int i;

	if (wilc && (wilc->vif[0]->ndev || wilc->vif[1]->ndev))
		unregister_inetaddr_notifier(&g_dev_notifier);

	if (wilc && wilc->firmware) {
		release_firmware(wilc->firmware);
		wilc->firmware = NULL;
	}

	if (wilc && (wilc->vif[0]->ndev || wilc->vif[1]->ndev)) {
		for (i = 0; i < NUM_CONCURRENT_IFC; i++)
			if (wilc->vif[i]->ndev)
				if (wilc->vif[i]->mac_opened)
					wilc_mac_close(wilc->vif[i]->ndev);

		for (i = 0; i < NUM_CONCURRENT_IFC; i++) {
			unregister_netdev(wilc->vif[i]->ndev);
			wilc_free_wiphy(wilc->vif[i]->ndev);
			free_netdev(wilc->vif[i]->ndev);
		}
	}

	kfree(wilc);
}