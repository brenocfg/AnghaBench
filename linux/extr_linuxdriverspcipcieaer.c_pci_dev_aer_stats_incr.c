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
typedef  int /*<<< orphan*/  u64 ;
struct pci_dev {struct aer_stats* aer_stats; } ;
struct aer_stats {int /*<<< orphan*/ * dev_fatal_errs; int /*<<< orphan*/  dev_total_fatal_errs; int /*<<< orphan*/ * dev_nonfatal_errs; int /*<<< orphan*/  dev_total_nonfatal_errs; int /*<<< orphan*/ * dev_cor_errs; int /*<<< orphan*/  dev_total_cor_errs; } ;
struct aer_err_info {int severity; int status; int mask; } ;

/* Variables and functions */
#define  AER_CORRECTABLE 130 
#define  AER_FATAL 129 
 int AER_MAX_TYPEOF_COR_ERRS ; 
 int AER_MAX_TYPEOF_UNCOR_ERRS ; 
#define  AER_NONFATAL 128 

__attribute__((used)) static void pci_dev_aer_stats_incr(struct pci_dev *pdev,
				   struct aer_err_info *info)
{
	int status, i, max = -1;
	u64 *counter = NULL;
	struct aer_stats *aer_stats = pdev->aer_stats;

	if (!aer_stats)
		return;

	switch (info->severity) {
	case AER_CORRECTABLE:
		aer_stats->dev_total_cor_errs++;
		counter = &aer_stats->dev_cor_errs[0];
		max = AER_MAX_TYPEOF_COR_ERRS;
		break;
	case AER_NONFATAL:
		aer_stats->dev_total_nonfatal_errs++;
		counter = &aer_stats->dev_nonfatal_errs[0];
		max = AER_MAX_TYPEOF_UNCOR_ERRS;
		break;
	case AER_FATAL:
		aer_stats->dev_total_fatal_errs++;
		counter = &aer_stats->dev_fatal_errs[0];
		max = AER_MAX_TYPEOF_UNCOR_ERRS;
		break;
	}

	status = (info->status & ~info->mask);
	for (i = 0; i < max; i++)
		if (status & (1 << i))
			counter[i]++;
}