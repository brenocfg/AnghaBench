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
struct sk_buff {char* data; int /*<<< orphan*/  truesize; } ;
struct pppoatm_vcc {int flags; int encaps; int /*<<< orphan*/  blocked; struct atm_vcc* atmvcc; } ;
struct ppp_channel {int dummy; } ;
struct atm_vcc {scalar_t__ (* send ) (struct atm_vcc*,struct sk_buff*) ;int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {struct atm_vcc* vcc; } ;

/* Variables and functions */
 TYPE_1__* ATM_SKB (struct sk_buff*) ; 
 int /*<<< orphan*/  ATM_VF_CLOSE ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 int /*<<< orphan*/  ATM_VF_RELEASED ; 
 int /*<<< orphan*/  BLOCKED ; 
 int DROP_PACKET ; 
 int LLC_LEN ; 
 int SC_COMP_PROT ; 
 int /*<<< orphan*/  atm_account_tx (struct atm_vcc*,struct sk_buff*) ; 
 int /*<<< orphan*/  bh_lock_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_unlock_sock (int /*<<< orphan*/ ) ; 
 struct pppoatm_vcc* chan_to_pvcc (struct ppp_channel*) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
#define  e_autodetect 130 
#define  e_llc 129 
#define  e_vc 128 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pppllc ; 
 int /*<<< orphan*/  pppoatm_may_send (struct pppoatm_vcc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  sk_atm (struct atm_vcc*) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,int) ; 
 scalar_t__ sock_owned_by_user (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct atm_vcc*,struct sk_buff*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pppoatm_send(struct ppp_channel *chan, struct sk_buff *skb)
{
	struct pppoatm_vcc *pvcc = chan_to_pvcc(chan);
	struct atm_vcc *vcc;
	int ret;

	ATM_SKB(skb)->vcc = pvcc->atmvcc;
	pr_debug("(skb=0x%p, vcc=0x%p)\n", skb, pvcc->atmvcc);
	if (skb->data[0] == '\0' && (pvcc->flags & SC_COMP_PROT))
		(void) skb_pull(skb, 1);

	vcc = ATM_SKB(skb)->vcc;
	bh_lock_sock(sk_atm(vcc));
	if (sock_owned_by_user(sk_atm(vcc))) {
		/*
		 * Needs to happen (and be flushed, hence test_and_) before we unlock
		 * the socket. It needs to be seen by the time our ->release_cb gets
		 * called.
		 */
		test_and_set_bit(BLOCKED, &pvcc->blocked);
		goto nospace;
	}
	if (test_bit(ATM_VF_RELEASED, &vcc->flags) ||
	    test_bit(ATM_VF_CLOSE, &vcc->flags) ||
	    !test_bit(ATM_VF_READY, &vcc->flags)) {
		bh_unlock_sock(sk_atm(vcc));
		kfree_skb(skb);
		return DROP_PACKET;
	}

	switch (pvcc->encaps) {		/* LLC encapsulation needed */
	case e_llc:
		if (skb_headroom(skb) < LLC_LEN) {
			struct sk_buff *n;
			n = skb_realloc_headroom(skb, LLC_LEN);
			if (n != NULL &&
			    !pppoatm_may_send(pvcc, n->truesize)) {
				kfree_skb(n);
				goto nospace;
			}
			consume_skb(skb);
			skb = n;
			if (skb == NULL) {
				bh_unlock_sock(sk_atm(vcc));
				return DROP_PACKET;
			}
		} else if (!pppoatm_may_send(pvcc, skb->truesize))
			goto nospace;
		memcpy(skb_push(skb, LLC_LEN), pppllc, LLC_LEN);
		break;
	case e_vc:
		if (!pppoatm_may_send(pvcc, skb->truesize))
			goto nospace;
		break;
	case e_autodetect:
		bh_unlock_sock(sk_atm(vcc));
		pr_debug("Trying to send without setting encaps!\n");
		kfree_skb(skb);
		return 1;
	}

	atm_account_tx(vcc, skb);
	pr_debug("atm_skb(%p)->vcc(%p)->dev(%p)\n",
		 skb, ATM_SKB(skb)->vcc, ATM_SKB(skb)->vcc->dev);
	ret = ATM_SKB(skb)->vcc->send(ATM_SKB(skb)->vcc, skb)
	    ? DROP_PACKET : 1;
	bh_unlock_sock(sk_atm(vcc));
	return ret;
nospace:
	bh_unlock_sock(sk_atm(vcc));
	/*
	 * We don't have space to send this SKB now, but we might have
	 * already applied SC_COMP_PROT compression, so may need to undo
	 */
	if ((pvcc->flags & SC_COMP_PROT) && skb_headroom(skb) > 0 &&
	    skb->data[-1] == '\0')
		(void) skb_push(skb, 1);
	return 0;
}