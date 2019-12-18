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
typedef  void* u8 ;
struct nci_nfcee_mode_set_cmd {void* nfcee_mode; void* nfcee_id; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_CMD_TIMEOUT ; 
 int __nci_request (struct nci_dev*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_nfcee_mode_set_req ; 

int nci_nfcee_mode_set(struct nci_dev *ndev, u8 nfcee_id, u8 nfcee_mode)
{
	struct nci_nfcee_mode_set_cmd cmd;

	cmd.nfcee_id = nfcee_id;
	cmd.nfcee_mode = nfcee_mode;

	return __nci_request(ndev, nci_nfcee_mode_set_req,
			     (unsigned long)&cmd,
			     msecs_to_jiffies(NCI_CMD_TIMEOUT));
}