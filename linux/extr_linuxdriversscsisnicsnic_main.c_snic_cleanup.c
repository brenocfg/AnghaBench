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
struct snic {unsigned int intr_count; unsigned int wq_count; unsigned int cq_count; int /*<<< orphan*/ * req_pool; int /*<<< orphan*/ * intr; int /*<<< orphan*/ * cq; int /*<<< orphan*/ * wq; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 unsigned int SNIC_REQ_MAX_CACHES ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snic_free_all_untagged_reqs (struct snic*) ; 
 int /*<<< orphan*/  snic_free_wq_buf ; 
 int /*<<< orphan*/  snic_fwcq_cmpl_handler (struct snic*,int) ; 
 int /*<<< orphan*/  snic_shutdown_scsi_cleanup (struct snic*) ; 
 int /*<<< orphan*/  snic_wq_cmpl_handler (struct snic*,int) ; 
 int /*<<< orphan*/  svnic_cq_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svnic_dev_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svnic_intr_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svnic_intr_mask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svnic_wq_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int svnic_wq_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snic_cleanup(struct snic *snic)
{
	unsigned int i;
	int ret;

	svnic_dev_disable(snic->vdev);
	for (i = 0; i < snic->intr_count; i++)
		svnic_intr_mask(&snic->intr[i]);

	for (i = 0; i < snic->wq_count; i++) {
		ret = svnic_wq_disable(&snic->wq[i]);
		if (ret)
			return ret;
	}

	/* Clean up completed IOs */
	snic_fwcq_cmpl_handler(snic, -1);

	snic_wq_cmpl_handler(snic, -1);

	/* Clean up the IOs that have not completed */
	for (i = 0; i < snic->wq_count; i++)
		svnic_wq_clean(&snic->wq[i], snic_free_wq_buf);

	for (i = 0; i < snic->cq_count; i++)
		svnic_cq_clean(&snic->cq[i]);

	for (i = 0; i < snic->intr_count; i++)
		svnic_intr_clean(&snic->intr[i]);

	/* Cleanup snic specific requests */
	snic_free_all_untagged_reqs(snic);

	/* Cleanup Pending SCSI commands */
	snic_shutdown_scsi_cleanup(snic);

	for (i = 0; i < SNIC_REQ_MAX_CACHES; i++)
		mempool_destroy(snic->req_pool[i]);

	return 0;
}