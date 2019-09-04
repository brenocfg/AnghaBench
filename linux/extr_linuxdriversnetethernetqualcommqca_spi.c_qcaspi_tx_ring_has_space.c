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
struct tx_ring {size_t tail; scalar_t__ size; scalar_t__* skb; } ;

/* Variables and functions */
 scalar_t__ QCAFRM_MAX_LEN ; 
 scalar_t__ QCASPI_HW_BUF_LEN ; 

__attribute__((used)) static int
qcaspi_tx_ring_has_space(struct tx_ring *txr)
{
	if (txr->skb[txr->tail])
		return 0;

	return (txr->size + QCAFRM_MAX_LEN < QCASPI_HW_BUF_LEN) ? 1 : 0;
}