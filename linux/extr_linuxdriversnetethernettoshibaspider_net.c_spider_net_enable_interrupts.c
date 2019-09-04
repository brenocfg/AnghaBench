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
 int /*<<< orphan*/  SPIDER_NET_GHIINT0MSK ; 
 int /*<<< orphan*/  SPIDER_NET_GHIINT1MSK ; 
 int /*<<< orphan*/  SPIDER_NET_GHIINT2MSK ; 
 int /*<<< orphan*/  SPIDER_NET_INT0_MASK_VALUE ; 
 int /*<<< orphan*/  SPIDER_NET_INT1_MASK_VALUE ; 
 int /*<<< orphan*/  SPIDER_NET_INT2_MASK_VALUE ; 
 int /*<<< orphan*/  spider_net_write_reg (struct spider_net_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spider_net_enable_interrupts(struct spider_net_card *card)
{
	spider_net_write_reg(card, SPIDER_NET_GHIINT0MSK,
			     SPIDER_NET_INT0_MASK_VALUE);
	spider_net_write_reg(card, SPIDER_NET_GHIINT1MSK,
			     SPIDER_NET_INT1_MASK_VALUE);
	spider_net_write_reg(card, SPIDER_NET_GHIINT2MSK,
			     SPIDER_NET_INT2_MASK_VALUE);
}