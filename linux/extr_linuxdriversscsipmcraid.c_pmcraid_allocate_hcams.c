#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * msg; int /*<<< orphan*/  ignore; void* hcam; int /*<<< orphan*/  baddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  ignore; int /*<<< orphan*/ * msg; void* hcam; int /*<<< orphan*/  baddr; } ;
struct pmcraid_instance {TYPE_2__ ldn; TYPE_1__ ccn; int /*<<< orphan*/  pdev; } ;
struct pmcraid_hcam_ldn {int dummy; } ;
struct pmcraid_hcam_ccn_ext {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PMCRAID_AEN_HDR_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmcraid_release_hcams (struct pmcraid_instance*) ; 

__attribute__((used)) static int pmcraid_allocate_hcams(struct pmcraid_instance *pinstance)
{
	pinstance->ccn.msg = pci_alloc_consistent(
					pinstance->pdev,
					PMCRAID_AEN_HDR_SIZE +
					sizeof(struct pmcraid_hcam_ccn_ext),
					&(pinstance->ccn.baddr));

	pinstance->ldn.msg = pci_alloc_consistent(
					pinstance->pdev,
					PMCRAID_AEN_HDR_SIZE +
					sizeof(struct pmcraid_hcam_ldn),
					&(pinstance->ldn.baddr));

	if (pinstance->ldn.msg == NULL || pinstance->ccn.msg == NULL) {
		pmcraid_release_hcams(pinstance);
	} else {
		pinstance->ccn.hcam =
			(void *)pinstance->ccn.msg + PMCRAID_AEN_HDR_SIZE;
		pinstance->ldn.hcam =
			(void *)pinstance->ldn.msg + PMCRAID_AEN_HDR_SIZE;

		atomic_set(&pinstance->ccn.ignore, 0);
		atomic_set(&pinstance->ldn.ignore, 0);
	}

	return (pinstance->ldn.msg == NULL) ? -ENOMEM : 0;
}