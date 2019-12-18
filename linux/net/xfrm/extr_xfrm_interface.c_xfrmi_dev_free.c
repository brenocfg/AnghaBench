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
struct xfrm_if {int /*<<< orphan*/  gro_cells; } ;
struct net_device {int /*<<< orphan*/  tstats; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gro_cells_destroy (int /*<<< orphan*/ *) ; 
 struct xfrm_if* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void xfrmi_dev_free(struct net_device *dev)
{
	struct xfrm_if *xi = netdev_priv(dev);

	gro_cells_destroy(&xi->gro_cells);
	free_percpu(dev->tstats);
}