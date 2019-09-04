#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct st21nfca_hci_info {scalar_t__ state; int /*<<< orphan*/  info_lock; int /*<<< orphan*/  phy_id; TYPE_1__* phy_ops; } ;
struct nfc_hci_dev {int dummy; } ;
struct TYPE_2__ {int (* enable ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ ST21NFCA_ST_COLD ; 
 scalar_t__ ST21NFCA_ST_READY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct st21nfca_hci_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st21nfca_hci_open(struct nfc_hci_dev *hdev)
{
	struct st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);
	int r;

	mutex_lock(&info->info_lock);

	if (info->state != ST21NFCA_ST_COLD) {
		r = -EBUSY;
		goto out;
	}

	r = info->phy_ops->enable(info->phy_id);

	if (r == 0)
		info->state = ST21NFCA_ST_READY;

out:
	mutex_unlock(&info->info_lock);
	return r;
}