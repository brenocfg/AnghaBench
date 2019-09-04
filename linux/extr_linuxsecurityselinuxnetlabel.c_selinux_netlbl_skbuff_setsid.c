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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sock {struct sk_security_struct* sk_security; } ;
struct sk_security_struct {scalar_t__ nlbl_state; } ;
struct sk_buff {int dummy; } ;
struct netlbl_lsm_secattr {int dummy; } ;

/* Variables and functions */
 scalar_t__ NLBL_REQSKB ; 
 int /*<<< orphan*/  netlbl_secattr_destroy (struct netlbl_lsm_secattr*) ; 
 int /*<<< orphan*/  netlbl_secattr_init (struct netlbl_lsm_secattr*) ; 
 int netlbl_skbuff_setattr (struct sk_buff*,int /*<<< orphan*/ ,struct netlbl_lsm_secattr*) ; 
 int security_netlbl_sid_to_secattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct netlbl_lsm_secattr*) ; 
 struct netlbl_lsm_secattr* selinux_netlbl_sock_getattr (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selinux_state ; 
 struct sock* skb_to_full_sk (struct sk_buff*) ; 

int selinux_netlbl_skbuff_setsid(struct sk_buff *skb,
				 u16 family,
				 u32 sid)
{
	int rc;
	struct netlbl_lsm_secattr secattr_storage;
	struct netlbl_lsm_secattr *secattr = NULL;
	struct sock *sk;

	/* if this is a locally generated packet check to see if it is already
	 * being labeled by it's parent socket, if it is just exit */
	sk = skb_to_full_sk(skb);
	if (sk != NULL) {
		struct sk_security_struct *sksec = sk->sk_security;

		if (sksec->nlbl_state != NLBL_REQSKB)
			return 0;
		secattr = selinux_netlbl_sock_getattr(sk, sid);
	}
	if (secattr == NULL) {
		secattr = &secattr_storage;
		netlbl_secattr_init(secattr);
		rc = security_netlbl_sid_to_secattr(&selinux_state, sid,
						    secattr);
		if (rc != 0)
			goto skbuff_setsid_return;
	}

	rc = netlbl_skbuff_setattr(skb, family, secattr);

skbuff_setsid_return:
	if (secattr == &secattr_storage)
		netlbl_secattr_destroy(secattr);
	return rc;
}