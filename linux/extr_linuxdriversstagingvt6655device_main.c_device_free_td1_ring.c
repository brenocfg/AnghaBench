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
struct vnt_tx_desc {struct vnt_td_info* td_info; } ;
struct vnt_td_info {int /*<<< orphan*/  skb; } ;
struct TYPE_2__ {int* tx_descs; } ;
struct vnt_private {struct vnt_tx_desc* apTD1Rings; TYPE_1__ opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vnt_td_info*) ; 

__attribute__((used)) static void device_free_td1_ring(struct vnt_private *priv)
{
	int i;

	for (i = 0; i < priv->opts.tx_descs[1]; i++) {
		struct vnt_tx_desc *desc = &priv->apTD1Rings[i];
		struct vnt_td_info *td_info = desc->td_info;

		dev_kfree_skb(td_info->skb);
		kfree(desc->td_info);
	}
}