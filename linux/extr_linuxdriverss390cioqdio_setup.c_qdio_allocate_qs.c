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
struct qdio_irq {int /*<<< orphan*/  output_qs; int /*<<< orphan*/  input_qs; } ;

/* Variables and functions */
 int __qdio_allocate_qs (int /*<<< orphan*/ ,int) ; 

int qdio_allocate_qs(struct qdio_irq *irq_ptr, int nr_input_qs, int nr_output_qs)
{
	int rc;

	rc = __qdio_allocate_qs(irq_ptr->input_qs, nr_input_qs);
	if (rc)
		return rc;
	rc = __qdio_allocate_qs(irq_ptr->output_qs, nr_output_qs);
	return rc;
}