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
struct spider_net_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPIDER_NET_DMA_RX_FEND_VALUE ; 
 int /*<<< orphan*/  SPIDER_NET_GDADMACCNTR ; 
 int /*<<< orphan*/  spider_net_write_reg (struct spider_net_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
spider_net_disable_rxdmac(struct spider_net_card *card)
{
	spider_net_write_reg(card, SPIDER_NET_GDADMACCNTR,
			     SPIDER_NET_DMA_RX_FEND_VALUE);
}