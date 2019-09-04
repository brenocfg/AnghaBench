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
struct fnic {unsigned int raw_wq_count; unsigned int wq_copy_count; unsigned int rq_count; unsigned int cq_count; unsigned int intr_count; int /*<<< orphan*/ * intr; int /*<<< orphan*/ * cq; int /*<<< orphan*/ * rq; int /*<<< orphan*/ * wq_copy; int /*<<< orphan*/ * wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  vnic_cq_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_intr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_rq_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_wq_copy_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_wq_free (int /*<<< orphan*/ *) ; 

void fnic_free_vnic_resources(struct fnic *fnic)
{
	unsigned int i;

	for (i = 0; i < fnic->raw_wq_count; i++)
		vnic_wq_free(&fnic->wq[i]);

	for (i = 0; i < fnic->wq_copy_count; i++)
		vnic_wq_copy_free(&fnic->wq_copy[i]);

	for (i = 0; i < fnic->rq_count; i++)
		vnic_rq_free(&fnic->rq[i]);

	for (i = 0; i < fnic->cq_count; i++)
		vnic_cq_free(&fnic->cq[i]);

	for (i = 0; i < fnic->intr_count; i++)
		vnic_intr_free(&fnic->intr[i]);
}