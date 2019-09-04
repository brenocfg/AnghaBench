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
struct qdio_irq {int /*<<< orphan*/  dsci; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_thinint_irq (struct qdio_irq*) ; 
 scalar_t__ shared_ind (struct qdio_irq*) ; 
 int /*<<< orphan*/  xchg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void clear_nonshared_ind(struct qdio_irq *irq_ptr)
{
	if (!is_thinint_irq(irq_ptr))
		return;
	if (shared_ind(irq_ptr))
		return;
	xchg(irq_ptr->dsci, 0);
}