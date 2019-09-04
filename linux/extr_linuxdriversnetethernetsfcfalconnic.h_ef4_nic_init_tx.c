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
struct ef4_tx_queue {TYPE_2__* efx; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* tx_init ) (struct ef4_tx_queue*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ef4_tx_queue*) ; 

__attribute__((used)) static inline void ef4_nic_init_tx(struct ef4_tx_queue *tx_queue)
{
	tx_queue->efx->type->tx_init(tx_queue);
}