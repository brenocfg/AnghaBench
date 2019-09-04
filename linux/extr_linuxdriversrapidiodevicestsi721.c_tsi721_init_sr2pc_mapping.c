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
struct tsi721_device {int ibwin_cnt; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ TSI721_IBWIN_LB (int) ; 
 int TSI721_IBWIN_NUM ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tsi721_init_sr2pc_mapping(struct tsi721_device *priv)
{
	int i;

	/* Disable all SR2PC inbound windows */
	for (i = 0; i < TSI721_IBWIN_NUM; i++)
		iowrite32(0, priv->regs + TSI721_IBWIN_LB(i));
	priv->ibwin_cnt = TSI721_IBWIN_NUM;
}