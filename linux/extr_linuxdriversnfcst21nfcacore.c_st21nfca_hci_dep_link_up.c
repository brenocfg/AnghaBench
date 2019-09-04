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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  idx; } ;
struct st21nfca_hci_info {TYPE_1__ dep_info; } ;
struct nfc_target {int /*<<< orphan*/  idx; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 struct st21nfca_hci_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 
 int st21nfca_im_send_atr_req (struct nfc_hci_dev*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int st21nfca_hci_dep_link_up(struct nfc_hci_dev *hdev,
				    struct nfc_target *target, u8 comm_mode,
				    u8 *gb, size_t gb_len)
{
	struct st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	info->dep_info.idx = target->idx;
	return st21nfca_im_send_atr_req(hdev, gb, gb_len);
}