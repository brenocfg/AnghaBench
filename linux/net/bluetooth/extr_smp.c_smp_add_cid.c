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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct smp_dev {int local_oob; struct crypto_shash* tfm_ecdh; struct crypto_shash* tfm_cmac; } ;
struct l2cap_chan {int /*<<< orphan*/  nesting; int /*<<< orphan*/ * ops; int /*<<< orphan*/  imtu; int /*<<< orphan*/  mode; int /*<<< orphan*/  state; int /*<<< orphan*/  src_type; int /*<<< orphan*/  src; struct smp_dev* data; } ;
struct hci_dev {int /*<<< orphan*/  bdaddr; } ;
struct crypto_shash {int dummy; } ;
typedef  struct crypto_shash crypto_kpp ;

/* Variables and functions */
 scalar_t__ ADDR_LE_DEV_PUBLIC ; 
 int /*<<< orphan*/  BDADDR_BREDR ; 
 int /*<<< orphan*/  BDADDR_LE_PUBLIC ; 
 int /*<<< orphan*/  BDADDR_LE_RANDOM ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  BT_LISTEN ; 
 int /*<<< orphan*/  CRYPTO_ALG_INTERNAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct l2cap_chan* ERR_CAST (struct crypto_shash*) ; 
 struct l2cap_chan* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int /*<<< orphan*/  L2CAP_CID_SMP ; 
 int /*<<< orphan*/  L2CAP_CID_SMP_BREDR ; 
 int /*<<< orphan*/  L2CAP_DEFAULT_MTU ; 
 int /*<<< orphan*/  L2CAP_MODE_BASIC ; 
 int /*<<< orphan*/  L2CAP_NESTING_PARENT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct crypto_shash* crypto_alloc_kpp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_shash* crypto_alloc_shash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_kpp (struct crypto_shash*) ; 
 int /*<<< orphan*/  crypto_free_shash (struct crypto_shash*) ; 
 int /*<<< orphan*/  hci_copy_identity_address (struct hci_dev*,int /*<<< orphan*/ *,scalar_t__*) ; 
 struct smp_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct smp_dev*) ; 
 int /*<<< orphan*/  l2cap_add_scid (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 struct l2cap_chan* l2cap_chan_create () ; 
 int /*<<< orphan*/  l2cap_chan_set_defaults (struct l2cap_chan*) ; 
 int /*<<< orphan*/  smp_root_chan_ops ; 

__attribute__((used)) static struct l2cap_chan *smp_add_cid(struct hci_dev *hdev, u16 cid)
{
	struct l2cap_chan *chan;
	struct smp_dev *smp;
	struct crypto_shash *tfm_cmac;
	struct crypto_kpp *tfm_ecdh;

	if (cid == L2CAP_CID_SMP_BREDR) {
		smp = NULL;
		goto create_chan;
	}

	smp = kzalloc(sizeof(*smp), GFP_KERNEL);
	if (!smp)
		return ERR_PTR(-ENOMEM);

	tfm_cmac = crypto_alloc_shash("cmac(aes)", 0, 0);
	if (IS_ERR(tfm_cmac)) {
		BT_ERR("Unable to create CMAC crypto context");
		kzfree(smp);
		return ERR_CAST(tfm_cmac);
	}

	tfm_ecdh = crypto_alloc_kpp("ecdh", CRYPTO_ALG_INTERNAL, 0);
	if (IS_ERR(tfm_ecdh)) {
		BT_ERR("Unable to create ECDH crypto context");
		crypto_free_shash(tfm_cmac);
		kzfree(smp);
		return ERR_CAST(tfm_ecdh);
	}

	smp->local_oob = false;
	smp->tfm_cmac = tfm_cmac;
	smp->tfm_ecdh = tfm_ecdh;

create_chan:
	chan = l2cap_chan_create();
	if (!chan) {
		if (smp) {
			crypto_free_shash(smp->tfm_cmac);
			crypto_free_kpp(smp->tfm_ecdh);
			kzfree(smp);
		}
		return ERR_PTR(-ENOMEM);
	}

	chan->data = smp;

	l2cap_add_scid(chan, cid);

	l2cap_chan_set_defaults(chan);

	if (cid == L2CAP_CID_SMP) {
		u8 bdaddr_type;

		hci_copy_identity_address(hdev, &chan->src, &bdaddr_type);

		if (bdaddr_type == ADDR_LE_DEV_PUBLIC)
			chan->src_type = BDADDR_LE_PUBLIC;
		else
			chan->src_type = BDADDR_LE_RANDOM;
	} else {
		bacpy(&chan->src, &hdev->bdaddr);
		chan->src_type = BDADDR_BREDR;
	}

	chan->state = BT_LISTEN;
	chan->mode = L2CAP_MODE_BASIC;
	chan->imtu = L2CAP_DEFAULT_MTU;
	chan->ops = &smp_root_chan_ops;

	/* Set correct nesting level for a parent/listening channel */
	atomic_set(&chan->nesting, L2CAP_NESTING_PARENT);

	return chan;
}