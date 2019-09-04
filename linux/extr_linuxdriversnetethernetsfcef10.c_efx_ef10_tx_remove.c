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
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct efx_tx_queue {TYPE_1__ txd; int /*<<< orphan*/  efx; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_nic_free_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void efx_ef10_tx_remove(struct efx_tx_queue *tx_queue)
{
	efx_nic_free_buffer(tx_queue->efx, &tx_queue->txd.buf);
}