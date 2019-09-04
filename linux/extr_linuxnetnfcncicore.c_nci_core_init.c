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
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_INIT_TIMEOUT ; 
 int __nci_request (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_init_req ; 

int nci_core_init(struct nci_dev *ndev)
{
	return __nci_request(ndev, nci_init_req, 0,
			     msecs_to_jiffies(NCI_INIT_TIMEOUT));
}