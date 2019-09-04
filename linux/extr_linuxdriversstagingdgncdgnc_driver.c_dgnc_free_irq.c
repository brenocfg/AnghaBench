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
struct dgnc_board {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct dgnc_board*) ; 

__attribute__((used)) static void dgnc_free_irq(struct dgnc_board *brd)
{
	if (brd->irq)
		free_irq(brd->irq, brd);
}