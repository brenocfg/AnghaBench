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
struct socket_smack {struct smack_known* smk_out; struct smack_known* smk_packet; struct smack_known* smk_in; } ;
struct sock {struct socket_smack* sk_security; } ;
struct smk_audit_info {int dummy; } ;
struct smack_known {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_MAC_OVERRIDE ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 int /*<<< orphan*/  smack_privileged (int /*<<< orphan*/ ) ; 
 int smk_access (struct smack_known*,struct smack_known*,int /*<<< orphan*/ ,struct smk_audit_info*) ; 
 int smk_bu_note (char*,struct smack_known*,struct smack_known*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smack_unix_stream_connect(struct sock *sock,
				     struct sock *other, struct sock *newsk)
{
	struct smack_known *skp;
	struct smack_known *okp;
	struct socket_smack *ssp = sock->sk_security;
	struct socket_smack *osp = other->sk_security;
	struct socket_smack *nsp = newsk->sk_security;
	struct smk_audit_info ad;
	int rc = 0;
#ifdef CONFIG_AUDIT
	struct lsm_network_audit net;
#endif

	if (!smack_privileged(CAP_MAC_OVERRIDE)) {
		skp = ssp->smk_out;
		okp = osp->smk_in;
#ifdef CONFIG_AUDIT
		smk_ad_init_net(&ad, __func__, LSM_AUDIT_DATA_NET, &net);
		smk_ad_setfield_u_net_sk(&ad, other);
#endif
		rc = smk_access(skp, okp, MAY_WRITE, &ad);
		rc = smk_bu_note("UDS connect", skp, okp, MAY_WRITE, rc);
		if (rc == 0) {
			okp = osp->smk_out;
			skp = ssp->smk_in;
			rc = smk_access(okp, skp, MAY_WRITE, &ad);
			rc = smk_bu_note("UDS connect", okp, skp,
						MAY_WRITE, rc);
		}
	}

	/*
	 * Cross reference the peer labels for SO_PEERSEC.
	 */
	if (rc == 0) {
		nsp->smk_packet = ssp->smk_out;
		ssp->smk_packet = osp->smk_out;
	}

	return rc;
}