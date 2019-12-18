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
struct TYPE_4__ {int* b; } ;
typedef  TYPE_1__ bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,TYPE_1__*) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int smp_ah (int /*<<< orphan*/  const*,int*,int*) ; 

int smp_generate_rpa(struct hci_dev *hdev, const u8 irk[16], bdaddr_t *rpa)
{
	struct l2cap_chan *chan = hdev->smp_data;
	struct smp_dev *smp;
	int err;

	if (!chan || !chan->data)
		return -EOPNOTSUPP;

	smp = chan->data;

	get_random_bytes(&rpa->b[3], 3);

	rpa->b[5] &= 0x3f;	/* Clear two most significant bits */
	rpa->b[5] |= 0x40;	/* Set second most significant bit */

	err = smp_ah(irk, &rpa->b[3], rpa->b);
	if (err < 0)
		return err;

	BT_DBG("RPA %pMR", rpa);

	return 0;
}