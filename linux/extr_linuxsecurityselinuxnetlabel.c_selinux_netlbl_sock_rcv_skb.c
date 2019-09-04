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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_security_struct {int /*<<< orphan*/  sclass; int /*<<< orphan*/  sid; } ;
struct sk_buff {int dummy; } ;
struct netlbl_lsm_secattr {scalar_t__ flags; } ;
struct common_audit_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ NETLBL_SECATTR_NONE ; 
 scalar_t__ RAWIP_SOCKET__RECVFROM ; 
#define  SECCLASS_TCP_SOCKET 129 
#define  SECCLASS_UDP_SOCKET 128 
 scalar_t__ SECINITSID_UNLABELED ; 
 scalar_t__ TCP_SOCKET__RECVFROM ; 
 scalar_t__ UDP_SOCKET__RECVFROM ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,struct common_audit_data*) ; 
 int /*<<< orphan*/  netlbl_enabled () ; 
 int /*<<< orphan*/  netlbl_secattr_destroy (struct netlbl_lsm_secattr*) ; 
 int /*<<< orphan*/  netlbl_secattr_init (struct netlbl_lsm_secattr*) ; 
 int /*<<< orphan*/  netlbl_skbuff_err (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int netlbl_skbuff_getattr (struct sk_buff*,int /*<<< orphan*/ ,struct netlbl_lsm_secattr*) ; 
 int selinux_netlbl_sidlookup_cached (struct sk_buff*,int /*<<< orphan*/ ,struct netlbl_lsm_secattr*,scalar_t__*) ; 
 int /*<<< orphan*/  selinux_state ; 

int selinux_netlbl_sock_rcv_skb(struct sk_security_struct *sksec,
				struct sk_buff *skb,
				u16 family,
				struct common_audit_data *ad)
{
	int rc;
	u32 nlbl_sid;
	u32 perm;
	struct netlbl_lsm_secattr secattr;

	if (!netlbl_enabled())
		return 0;

	netlbl_secattr_init(&secattr);
	rc = netlbl_skbuff_getattr(skb, family, &secattr);
	if (rc == 0 && secattr.flags != NETLBL_SECATTR_NONE)
		rc = selinux_netlbl_sidlookup_cached(skb, family,
						     &secattr, &nlbl_sid);
	else
		nlbl_sid = SECINITSID_UNLABELED;
	netlbl_secattr_destroy(&secattr);
	if (rc != 0)
		return rc;

	switch (sksec->sclass) {
	case SECCLASS_UDP_SOCKET:
		perm = UDP_SOCKET__RECVFROM;
		break;
	case SECCLASS_TCP_SOCKET:
		perm = TCP_SOCKET__RECVFROM;
		break;
	default:
		perm = RAWIP_SOCKET__RECVFROM;
	}

	rc = avc_has_perm(&selinux_state,
			  sksec->sid, nlbl_sid, sksec->sclass, perm, ad);
	if (rc == 0)
		return 0;

	if (nlbl_sid != SECINITSID_UNLABELED)
		netlbl_skbuff_err(skb, family, rc, 0);
	return rc;
}