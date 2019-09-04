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
struct TYPE_2__ {int num_queues; } ;
struct dpaa2_eth_priv {TYPE_1__ dpni_attrs; } ;

/* Variables and functions */

__attribute__((used)) static int dpaa2_eth_queue_count(struct dpaa2_eth_priv *priv)
{
	return priv->dpni_attrs.num_queues;
}