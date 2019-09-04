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
struct fdp_nci_info {int setup_patch_sent; int /*<<< orphan*/  setup_wq; } ;

/* Variables and functions */
 struct fdp_nci_info* nci_get_drvdata (struct nci_dev*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fdp_nci_send_patch_cb(struct nci_dev *ndev)
{
	struct fdp_nci_info *info = nci_get_drvdata(ndev);

	info->setup_patch_sent = 1;
	wake_up(&info->setup_wq);
}