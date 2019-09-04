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
struct ef4_tx_queue {int queue; } ;

/* Variables and functions */
 int EF4_TXQ_TYPE_OFFLOAD ; 

__attribute__((used)) static inline struct ef4_tx_queue *ef4_tx_queue_partner(struct ef4_tx_queue *tx_queue)
{
	if (tx_queue->queue & EF4_TXQ_TYPE_OFFLOAD)
		return tx_queue - EF4_TXQ_TYPE_OFFLOAD;
	else
		return tx_queue + EF4_TXQ_TYPE_OFFLOAD;
}