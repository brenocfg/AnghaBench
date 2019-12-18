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
struct smp_dev {int /*<<< orphan*/  tfm_ecdh; int /*<<< orphan*/  tfm_cmac; } ;
struct l2cap_chan {struct smp_dev* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*) ; 
 int /*<<< orphan*/  crypto_free_kpp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct smp_dev*) ; 
 int /*<<< orphan*/  l2cap_chan_put (struct l2cap_chan*) ; 

__attribute__((used)) static void smp_del_chan(struct l2cap_chan *chan)
{
	struct smp_dev *smp;

	BT_DBG("chan %p", chan);

	smp = chan->data;
	if (smp) {
		chan->data = NULL;
		crypto_free_shash(smp->tfm_cmac);
		crypto_free_kpp(smp->tfm_ecdh);
		kzfree(smp);
	}

	l2cap_chan_put(chan);
}