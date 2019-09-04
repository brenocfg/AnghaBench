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
struct ef4_tx_queue {scalar_t__ ptr_mask; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (scalar_t__,int) ; 
 int EF4_TX_CB_ORDER ; 
 int PAGE_SIZE ; 

__attribute__((used)) static unsigned int ef4_tx_cb_page_count(struct ef4_tx_queue *tx_queue)
{
	return DIV_ROUND_UP(tx_queue->ptr_mask + 1, PAGE_SIZE >> EF4_TX_CB_ORDER);
}