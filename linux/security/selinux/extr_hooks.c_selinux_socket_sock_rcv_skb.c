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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct sock {scalar_t__ sk_family; struct sk_security_struct* sk_security; } ;
struct sk_security_struct {int /*<<< orphan*/  sid; } ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  secmark; int /*<<< orphan*/  skb_iif; } ;
struct lsm_network_audit {scalar_t__ family; int /*<<< orphan*/  netif; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {struct lsm_network_audit* net; } ;
struct common_audit_data {TYPE_1__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  LSM_AUDIT_DATA_NET ; 
 int /*<<< orphan*/  PACKET__RECV ; 
 int /*<<< orphan*/  PEER__RECV ; 
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 int /*<<< orphan*/  SECCLASS_PACKET ; 
 int /*<<< orphan*/  SECCLASS_PEER ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int selinux_inet_sys_rcv_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 int /*<<< orphan*/  selinux_netlbl_err (struct sk_buff*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int selinux_parse_skb (struct sk_buff*,struct common_audit_data*,char**,int,int /*<<< orphan*/ *) ; 
 scalar_t__ selinux_peerlbl_enabled () ; 
 int /*<<< orphan*/  selinux_policycap_netpeer () ; 
 scalar_t__ selinux_secmark_enabled () ; 
 int selinux_skb_peerlbl_sid (struct sk_buff*,scalar_t__,int /*<<< orphan*/ *) ; 
 int selinux_sock_rcv_skb_compat (struct sock*,struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  selinux_state ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static int selinux_socket_sock_rcv_skb(struct sock *sk, struct sk_buff *skb)
{
	int err;
	struct sk_security_struct *sksec = sk->sk_security;
	u16 family = sk->sk_family;
	u32 sk_sid = sksec->sid;
	struct common_audit_data ad;
	struct lsm_network_audit net = {0,};
	char *addrp;
	u8 secmark_active;
	u8 peerlbl_active;

	if (family != PF_INET && family != PF_INET6)
		return 0;

	/* Handle mapped IPv4 packets arriving via IPv6 sockets */
	if (family == PF_INET6 && skb->protocol == htons(ETH_P_IP))
		family = PF_INET;

	/* If any sort of compatibility mode is enabled then handoff processing
	 * to the selinux_sock_rcv_skb_compat() function to deal with the
	 * special handling.  We do this in an attempt to keep this function
	 * as fast and as clean as possible. */
	if (!selinux_policycap_netpeer())
		return selinux_sock_rcv_skb_compat(sk, skb, family);

	secmark_active = selinux_secmark_enabled();
	peerlbl_active = selinux_peerlbl_enabled();
	if (!secmark_active && !peerlbl_active)
		return 0;

	ad.type = LSM_AUDIT_DATA_NET;
	ad.u.net = &net;
	ad.u.net->netif = skb->skb_iif;
	ad.u.net->family = family;
	err = selinux_parse_skb(skb, &ad, &addrp, 1, NULL);
	if (err)
		return err;

	if (peerlbl_active) {
		u32 peer_sid;

		err = selinux_skb_peerlbl_sid(skb, family, &peer_sid);
		if (err)
			return err;
		err = selinux_inet_sys_rcv_skb(sock_net(sk), skb->skb_iif,
					       addrp, family, peer_sid, &ad);
		if (err) {
			selinux_netlbl_err(skb, family, err, 0);
			return err;
		}
		err = avc_has_perm(&selinux_state,
				   sk_sid, peer_sid, SECCLASS_PEER,
				   PEER__RECV, &ad);
		if (err) {
			selinux_netlbl_err(skb, family, err, 0);
			return err;
		}
	}

	if (secmark_active) {
		err = avc_has_perm(&selinux_state,
				   sk_sid, skb->secmark, SECCLASS_PACKET,
				   PACKET__RECV, &ad);
		if (err)
			return err;
	}

	return err;
}