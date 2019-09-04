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
typedef  int u8 ;
struct TYPE_2__ {int valid_bit; } ;
struct qbman_swp {TYPE_1__ mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_wmb () ; 

void qbman_swp_mc_submit(struct qbman_swp *p, void *cmd, u8 cmd_verb)
{
	u8 *v = cmd;

	dma_wmb();
	*v = cmd_verb | p->mc.valid_bit;
}