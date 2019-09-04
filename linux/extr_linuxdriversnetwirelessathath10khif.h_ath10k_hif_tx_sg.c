#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ath10k_hif_sg_item {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct ath10k {TYPE_2__ hif; } ;
struct TYPE_3__ {int (* tx_sg ) (struct ath10k*,int /*<<< orphan*/ ,struct ath10k_hif_sg_item*,int) ;} ;

/* Variables and functions */
 int stub1 (struct ath10k*,int /*<<< orphan*/ ,struct ath10k_hif_sg_item*,int) ; 

__attribute__((used)) static inline int ath10k_hif_tx_sg(struct ath10k *ar, u8 pipe_id,
				   struct ath10k_hif_sg_item *items,
				   int n_items)
{
	return ar->hif.ops->tx_sg(ar, pipe_id, items, n_items);
}