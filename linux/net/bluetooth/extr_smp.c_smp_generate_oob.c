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
typedef  int /*<<< orphan*/  u8 ;
struct smp_dev {int debug_key; int local_oob; int /*<<< orphan*/  local_rand; int /*<<< orphan*/ * local_pk; int /*<<< orphan*/  tfm_cmac; int /*<<< orphan*/  tfm_ecdh; } ;
struct l2cap_chan {struct smp_dev* data; } ;
struct hci_dev {struct l2cap_chan* smp_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HCI_USE_DEBUG_KEYS ; 
 int /*<<< orphan*/  SMP_DBG (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_memneq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debug_pk ; 
 int /*<<< orphan*/  debug_sk ; 
 int generate_ecdh_keys (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int set_ecdh_privkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smp_f4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int smp_generate_oob(struct hci_dev *hdev, u8 hash[16], u8 rand[16])
{
	struct l2cap_chan *chan = hdev->smp_data;
	struct smp_dev *smp;
	int err;

	if (!chan || !chan->data)
		return -EOPNOTSUPP;

	smp = chan->data;

	if (hci_dev_test_flag(hdev, HCI_USE_DEBUG_KEYS)) {
		BT_DBG("Using debug keys");
		err = set_ecdh_privkey(smp->tfm_ecdh, debug_sk);
		if (err)
			return err;
		memcpy(smp->local_pk, debug_pk, 64);
		smp->debug_key = true;
	} else {
		while (true) {
			/* Generate key pair for Secure Connections */
			err = generate_ecdh_keys(smp->tfm_ecdh, smp->local_pk);
			if (err)
				return err;

			/* This is unlikely, but we need to check that
			 * we didn't accidentially generate a debug key.
			 */
			if (crypto_memneq(smp->local_pk, debug_pk, 64))
				break;
		}
		smp->debug_key = false;
	}

	SMP_DBG("OOB Public Key X: %32phN", smp->local_pk);
	SMP_DBG("OOB Public Key Y: %32phN", smp->local_pk + 32);

	get_random_bytes(smp->local_rand, 16);

	err = smp_f4(smp->tfm_cmac, smp->local_pk, smp->local_pk,
		     smp->local_rand, 0, hash);
	if (err < 0)
		return err;

	memcpy(rand, smp->local_rand, 16);

	smp->local_oob = true;

	return 0;
}