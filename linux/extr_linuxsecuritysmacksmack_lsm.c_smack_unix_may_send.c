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
struct socket_smack {int /*<<< orphan*/  smk_in; int /*<<< orphan*/  smk_out; } ;
struct socket {TYPE_1__* sk; } ;
struct smk_audit_info {int dummy; } ;
struct TYPE_2__ {struct socket_smack* sk_security; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_MAC_OVERRIDE ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 scalar_t__ smack_privileged (int /*<<< orphan*/ ) ; 
 int smk_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smk_audit_info*) ; 
 int smk_bu_note (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smack_unix_may_send(struct socket *sock, struct socket *other)
{
	struct socket_smack *ssp = sock->sk->sk_security;
	struct socket_smack *osp = other->sk->sk_security;
	struct smk_audit_info ad;
	int rc;

#ifdef CONFIG_AUDIT
	struct lsm_network_audit net;

	smk_ad_init_net(&ad, __func__, LSM_AUDIT_DATA_NET, &net);
	smk_ad_setfield_u_net_sk(&ad, other->sk);
#endif

	if (smack_privileged(CAP_MAC_OVERRIDE))
		return 0;

	rc = smk_access(ssp->smk_out, osp->smk_in, MAY_WRITE, &ad);
	rc = smk_bu_note("UDS send", ssp->smk_out, osp->smk_in, MAY_WRITE, rc);
	return rc;
}