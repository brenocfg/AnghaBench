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
struct efx_rx_queue {TYPE_2__* efx; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int (* rx_probe ) (struct efx_rx_queue*) ;} ;

/* Variables and functions */
 int stub1 (struct efx_rx_queue*) ; 

__attribute__((used)) static inline int efx_nic_probe_rx(struct efx_rx_queue *rx_queue)
{
	return rx_queue->efx->type->rx_probe(rx_queue);
}