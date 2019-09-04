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
struct vnt_rx_desc {int /*<<< orphan*/  rd_info; } ;
struct TYPE_2__ {int rx_descs1; } ;
struct vnt_private {struct vnt_rx_desc* aRD1Ring; TYPE_1__ opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_free_rx_buf (struct vnt_private*,struct vnt_rx_desc*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_free_rd1_ring(struct vnt_private *priv)
{
	int i;

	for (i = 0; i < priv->opts.rx_descs1; i++) {
		struct vnt_rx_desc *desc = &priv->aRD1Ring[i];

		device_free_rx_buf(priv, desc);
		kfree(desc->rd_info);
	}
}