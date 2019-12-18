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
struct smp_chan {int /*<<< orphan*/  tfm_cmac; int /*<<< orphan*/  security_timer; struct l2cap_conn* conn; int /*<<< orphan*/  tfm_ecdh; } ;
struct l2cap_conn {int /*<<< orphan*/  hcon; struct l2cap_chan* smp; } ;
struct l2cap_chan {struct smp_chan* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  CRYPTO_ALG_INTERNAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_ALLOW_CMD (struct smp_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_CMD_PAIRING_FAIL ; 
 int /*<<< orphan*/  crypto_alloc_kpp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_alloc_shash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_hold (int /*<<< orphan*/ ) ; 
 struct smp_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct smp_chan*) ; 
 int /*<<< orphan*/  smp_timeout ; 

__attribute__((used)) static struct smp_chan *smp_chan_create(struct l2cap_conn *conn)
{
	struct l2cap_chan *chan = conn->smp;
	struct smp_chan *smp;

	smp = kzalloc(sizeof(*smp), GFP_ATOMIC);
	if (!smp)
		return NULL;

	smp->tfm_cmac = crypto_alloc_shash("cmac(aes)", 0, 0);
	if (IS_ERR(smp->tfm_cmac)) {
		BT_ERR("Unable to create CMAC crypto context");
		goto zfree_smp;
	}

	smp->tfm_ecdh = crypto_alloc_kpp("ecdh", CRYPTO_ALG_INTERNAL, 0);
	if (IS_ERR(smp->tfm_ecdh)) {
		BT_ERR("Unable to create ECDH crypto context");
		goto free_shash;
	}

	smp->conn = conn;
	chan->data = smp;

	SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_FAIL);

	INIT_DELAYED_WORK(&smp->security_timer, smp_timeout);

	hci_conn_hold(conn->hcon);

	return smp;

free_shash:
	crypto_free_shash(smp->tfm_cmac);
zfree_smp:
	kzfree(smp);
	return NULL;
}