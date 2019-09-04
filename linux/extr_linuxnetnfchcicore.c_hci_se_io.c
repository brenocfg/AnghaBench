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
typedef  int /*<<< orphan*/  u32 ;
struct nfc_hci_dev {TYPE_1__* ops; } ;
struct nfc_dev {int dummy; } ;
typedef  int /*<<< orphan*/  se_io_cb_t ;
struct TYPE_2__ {int (* se_io ) (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 struct nfc_hci_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int stub1 (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int hci_se_io(struct nfc_dev *nfc_dev, u32 se_idx,
		     u8 *apdu, size_t apdu_length,
		     se_io_cb_t cb, void *cb_context)
{
	struct nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	if (hdev->ops->se_io)
		return hdev->ops->se_io(hdev, se_idx, apdu,
					apdu_length, cb, cb_context);

	return 0;
}