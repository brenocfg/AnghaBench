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
struct nfc_digital_dev {int /*<<< orphan*/  curr_protocol; } ;
struct nfc_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_PROTO_NFC_DEP ; 
 int digital_in_send_atr_req (struct nfc_digital_dev*,struct nfc_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 struct nfc_digital_dev* nfc_get_drvdata (struct nfc_dev*) ; 

__attribute__((used)) static int digital_dep_link_up(struct nfc_dev *nfc_dev,
			       struct nfc_target *target,
			       __u8 comm_mode, __u8 *gb, size_t gb_len)
{
	struct nfc_digital_dev *ddev = nfc_get_drvdata(nfc_dev);
	int rc;

	rc = digital_in_send_atr_req(ddev, target, comm_mode, gb, gb_len);

	if (!rc)
		ddev->curr_protocol = NFC_PROTO_NFC_DEP;

	return rc;
}