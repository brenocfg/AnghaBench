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
struct snic {unsigned int wq_count; unsigned int cq_count; unsigned int intr_count; int /*<<< orphan*/ * intr; int /*<<< orphan*/ * cq; int /*<<< orphan*/ * wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  svnic_cq_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svnic_intr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svnic_wq_free (int /*<<< orphan*/ *) ; 

void
snic_free_vnic_res(struct snic *snic)
{
	unsigned int i;

	for (i = 0; i < snic->wq_count; i++)
		svnic_wq_free(&snic->wq[i]);

	for (i = 0; i < snic->cq_count; i++)
		svnic_cq_free(&snic->cq[i]);

	for (i = 0; i < snic->intr_count; i++)
		svnic_intr_free(&snic->intr[i]);
}