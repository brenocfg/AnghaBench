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
struct nfc_target {int dummy; } ;
struct nci_dev {scalar_t__ n_targets; int /*<<< orphan*/  targets; } ;

/* Variables and functions */
 int NCI_MAX_DISCOVERED_TARGETS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void nci_clear_target_list(struct nci_dev *ndev)
{
	memset(ndev->targets, 0,
	       (sizeof(struct nfc_target)*NCI_MAX_DISCOVERED_TARGETS));

	ndev->n_targets = 0;
}