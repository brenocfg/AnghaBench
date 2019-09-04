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
struct sk_buff {scalar_t__ data; } ;
struct nci_dev {int dummy; } ;
struct nci_core_set_config_rsp {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  nci_req_complete (struct nci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nci_core_set_config_rsp_packet(struct nci_dev *ndev,
					   struct sk_buff *skb)
{
	struct nci_core_set_config_rsp *rsp = (void *) skb->data;

	pr_debug("status 0x%x\n", rsp->status);

	nci_req_complete(ndev, rsp->status);
}