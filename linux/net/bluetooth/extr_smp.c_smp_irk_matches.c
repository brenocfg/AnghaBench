#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct smp_dev {int dummy; } ;
struct l2cap_chan {struct smp_dev* data; } ;
struct hci_dev {struct l2cap_chan* smp_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * b; } ;
typedef  TYPE_1__ bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,TYPE_1__ const*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_memneq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int smp_ah (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool smp_irk_matches(struct hci_dev *hdev, const u8 irk[16],
		     const bdaddr_t *bdaddr)
{
	struct l2cap_chan *chan = hdev->smp_data;
	struct smp_dev *smp;
	u8 hash[3];
	int err;

	if (!chan || !chan->data)
		return false;

	smp = chan->data;

	BT_DBG("RPA %pMR IRK %*phN", bdaddr, 16, irk);

	err = smp_ah(irk, &bdaddr->b[3], hash);
	if (err)
		return false;

	return !crypto_memneq(bdaddr->b, hash, 3);
}