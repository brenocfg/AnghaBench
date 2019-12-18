#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct sk_security_struct {scalar_t__ sctp_assoc_state; scalar_t__ peer_sid; int /*<<< orphan*/  sid; int /*<<< orphan*/  sclass; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {TYPE_2__* sk; } ;
struct sctp_endpoint {scalar_t__ peer_secid; scalar_t__ secid; TYPE_3__ base; } ;
struct lsm_network_audit {TYPE_2__* sk; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {struct lsm_network_audit* net; } ;
struct common_audit_data {TYPE_1__ u; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  sk_family; struct sk_security_struct* sk_security; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_AUDIT_DATA_NET ; 
 scalar_t__ SCTP_ASSOC_SET ; 
 scalar_t__ SCTP_ASSOC_UNSET ; 
 int /*<<< orphan*/  SCTP_SOCKET__ASSOCIATION ; 
 scalar_t__ SECINITSID_UNLABELED ; 
 scalar_t__ SECSID_NULL ; 
 int avc_has_perm (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 int selinux_conn_sid (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int selinux_netlbl_sctp_assoc_request (struct sctp_endpoint*,struct sk_buff*) ; 
 scalar_t__ selinux_peerlbl_enabled () ; 
 int /*<<< orphan*/  selinux_policycap_extsockclass () ; 
 int selinux_skb_peerlbl_sid (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_sctp_assoc_request(struct sctp_endpoint *ep,
				      struct sk_buff *skb)
{
	struct sk_security_struct *sksec = ep->base.sk->sk_security;
	struct common_audit_data ad;
	struct lsm_network_audit net = {0,};
	u8 peerlbl_active;
	u32 peer_sid = SECINITSID_UNLABELED;
	u32 conn_sid;
	int err = 0;

	if (!selinux_policycap_extsockclass())
		return 0;

	peerlbl_active = selinux_peerlbl_enabled();

	if (peerlbl_active) {
		/* This will return peer_sid = SECSID_NULL if there are
		 * no peer labels, see security_net_peersid_resolve().
		 */
		err = selinux_skb_peerlbl_sid(skb, ep->base.sk->sk_family,
					      &peer_sid);
		if (err)
			return err;

		if (peer_sid == SECSID_NULL)
			peer_sid = SECINITSID_UNLABELED;
	}

	if (sksec->sctp_assoc_state == SCTP_ASSOC_UNSET) {
		sksec->sctp_assoc_state = SCTP_ASSOC_SET;

		/* Here as first association on socket. As the peer SID
		 * was allowed by peer recv (and the netif/node checks),
		 * then it is approved by policy and used as the primary
		 * peer SID for getpeercon(3).
		 */
		sksec->peer_sid = peer_sid;
	} else if  (sksec->peer_sid != peer_sid) {
		/* Other association peer SIDs are checked to enforce
		 * consistency among the peer SIDs.
		 */
		ad.type = LSM_AUDIT_DATA_NET;
		ad.u.net = &net;
		ad.u.net->sk = ep->base.sk;
		err = avc_has_perm(&selinux_state,
				   sksec->peer_sid, peer_sid, sksec->sclass,
				   SCTP_SOCKET__ASSOCIATION, &ad);
		if (err)
			return err;
	}

	/* Compute the MLS component for the connection and store
	 * the information in ep. This will be used by SCTP TCP type
	 * sockets and peeled off connections as they cause a new
	 * socket to be generated. selinux_sctp_sk_clone() will then
	 * plug this into the new socket.
	 */
	err = selinux_conn_sid(sksec->sid, peer_sid, &conn_sid);
	if (err)
		return err;

	ep->secid = conn_sid;
	ep->peer_secid = peer_sid;

	/* Set any NetLabel labels including CIPSO/CALIPSO options. */
	return selinux_netlbl_sctp_assoc_request(ep, skb);
}