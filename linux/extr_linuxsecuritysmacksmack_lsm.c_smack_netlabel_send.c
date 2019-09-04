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
struct socket_smack {struct smack_known* smk_out; } ;
struct sockaddr_in {int dummy; } ;
struct sock {struct socket_smack* sk_security; } ;
struct smk_audit_info {int dummy; } ;
struct smack_known {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAY_WRITE ; 
 int SMACK_CIPSO_SOCKET ; 
 int SMACK_UNLABELED_SOCKET ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct smack_known* smack_ipv4host_label (struct sockaddr_in*) ; 
 int smack_netlabel (struct sock*,int) ; 
 int smk_access (struct smack_known*,struct smack_known*,int /*<<< orphan*/ ,struct smk_audit_info*) ; 
 int smk_bu_note (char*,struct smack_known*,struct smack_known*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smack_netlabel_send(struct sock *sk, struct sockaddr_in *sap)
{
	struct smack_known *skp;
	int rc;
	int sk_lbl;
	struct smack_known *hkp;
	struct socket_smack *ssp = sk->sk_security;
	struct smk_audit_info ad;

	rcu_read_lock();
	hkp = smack_ipv4host_label(sap);
	if (hkp != NULL) {
#ifdef CONFIG_AUDIT
		struct lsm_network_audit net;

		smk_ad_init_net(&ad, __func__, LSM_AUDIT_DATA_NET, &net);
		ad.a.u.net->family = sap->sin_family;
		ad.a.u.net->dport = sap->sin_port;
		ad.a.u.net->v4info.daddr = sap->sin_addr.s_addr;
#endif
		sk_lbl = SMACK_UNLABELED_SOCKET;
		skp = ssp->smk_out;
		rc = smk_access(skp, hkp, MAY_WRITE, &ad);
		rc = smk_bu_note("IPv4 host check", skp, hkp, MAY_WRITE, rc);
	} else {
		sk_lbl = SMACK_CIPSO_SOCKET;
		rc = 0;
	}
	rcu_read_unlock();
	if (rc != 0)
		return rc;

	return smack_netlabel(sk, sk_lbl);
}