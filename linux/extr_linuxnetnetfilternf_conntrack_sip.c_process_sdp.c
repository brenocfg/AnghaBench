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
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct sk_buff {int dummy; } ;
struct sdp_media_type {int /*<<< orphan*/  class; scalar_t__ len; } ;
struct nf_nat_sip_hooks {int (* sdp_addr ) (struct sk_buff*,unsigned int,unsigned int,char const**,unsigned int*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union nf_inet_addr*) ;int (* sdp_session ) (struct sk_buff*,unsigned int,unsigned int,char const**,unsigned int*,unsigned int,union nf_inet_addr*) ;} ;
struct nf_conn {int status; } ;
typedef  int /*<<< orphan*/  rtp_addr ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int IPS_NAT_MASK ; 
 int NF_ACCEPT ; 
 int NF_DROP ; 
 int /*<<< orphan*/  SDP_HDR_CONNECTION ; 
 int /*<<< orphan*/  SDP_HDR_MEDIA ; 
 int /*<<< orphan*/  SDP_HDR_UNSPEC ; 
 int /*<<< orphan*/  SDP_HDR_VERSION ; 
 scalar_t__ ct_sip_get_sdp_header (struct nf_conn*,char const*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 scalar_t__ ct_sip_parse_sdp_addr (struct nf_conn*,char const*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,unsigned int*,union nf_inet_addr*) ; 
 int /*<<< orphan*/  htons (unsigned int) ; 
 int /*<<< orphan*/  memcpy (union nf_inet_addr*,union nf_inet_addr*,int) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_ct_helper_log (struct sk_buff*,struct nf_conn*,char*,...) ; 
 int /*<<< orphan*/  nf_nat_sip_hooks ; 
 struct nf_nat_sip_hooks* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct sdp_media_type* sdp_media_type (char const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sdp_media_types ; 
 int set_expected_rtp_rtcp (struct sk_buff*,unsigned int,unsigned int,char const**,unsigned int*,union nf_inet_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 int stub1 (struct sk_buff*,unsigned int,unsigned int,char const**,unsigned int*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union nf_inet_addr*) ; 
 int stub2 (struct sk_buff*,unsigned int,unsigned int,char const**,unsigned int*,unsigned int,union nf_inet_addr*) ; 

__attribute__((used)) static int process_sdp(struct sk_buff *skb, unsigned int protoff,
		       unsigned int dataoff,
		       const char **dptr, unsigned int *datalen,
		       unsigned int cseq)
{
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	unsigned int matchoff, matchlen;
	unsigned int mediaoff, medialen;
	unsigned int sdpoff;
	unsigned int caddr_len, maddr_len;
	unsigned int i;
	union nf_inet_addr caddr, maddr, rtp_addr;
	const struct nf_nat_sip_hooks *hooks;
	unsigned int port;
	const struct sdp_media_type *t;
	int ret = NF_ACCEPT;

	hooks = rcu_dereference(nf_nat_sip_hooks);

	/* Find beginning of session description */
	if (ct_sip_get_sdp_header(ct, *dptr, 0, *datalen,
				  SDP_HDR_VERSION, SDP_HDR_UNSPEC,
				  &matchoff, &matchlen) <= 0)
		return NF_ACCEPT;
	sdpoff = matchoff;

	/* The connection information is contained in the session description
	 * and/or once per media description. The first media description marks
	 * the end of the session description. */
	caddr_len = 0;
	if (ct_sip_parse_sdp_addr(ct, *dptr, sdpoff, *datalen,
				  SDP_HDR_CONNECTION, SDP_HDR_MEDIA,
				  &matchoff, &matchlen, &caddr) > 0)
		caddr_len = matchlen;

	mediaoff = sdpoff;
	for (i = 0; i < ARRAY_SIZE(sdp_media_types); ) {
		if (ct_sip_get_sdp_header(ct, *dptr, mediaoff, *datalen,
					  SDP_HDR_MEDIA, SDP_HDR_UNSPEC,
					  &mediaoff, &medialen) <= 0)
			break;

		/* Get media type and port number. A media port value of zero
		 * indicates an inactive stream. */
		t = sdp_media_type(*dptr, mediaoff, medialen);
		if (!t) {
			mediaoff += medialen;
			continue;
		}
		mediaoff += t->len;
		medialen -= t->len;

		port = simple_strtoul(*dptr + mediaoff, NULL, 10);
		if (port == 0)
			continue;
		if (port < 1024 || port > 65535) {
			nf_ct_helper_log(skb, ct, "wrong port %u", port);
			return NF_DROP;
		}

		/* The media description overrides the session description. */
		maddr_len = 0;
		if (ct_sip_parse_sdp_addr(ct, *dptr, mediaoff, *datalen,
					  SDP_HDR_CONNECTION, SDP_HDR_MEDIA,
					  &matchoff, &matchlen, &maddr) > 0) {
			maddr_len = matchlen;
			memcpy(&rtp_addr, &maddr, sizeof(rtp_addr));
		} else if (caddr_len)
			memcpy(&rtp_addr, &caddr, sizeof(rtp_addr));
		else {
			nf_ct_helper_log(skb, ct, "cannot parse SDP message");
			return NF_DROP;
		}

		ret = set_expected_rtp_rtcp(skb, protoff, dataoff,
					    dptr, datalen,
					    &rtp_addr, htons(port), t->class,
					    mediaoff, medialen);
		if (ret != NF_ACCEPT) {
			nf_ct_helper_log(skb, ct,
					 "cannot add expectation for voice");
			return ret;
		}

		/* Update media connection address if present */
		if (maddr_len && hooks && ct->status & IPS_NAT_MASK) {
			ret = hooks->sdp_addr(skb, protoff, dataoff,
					      dptr, datalen, mediaoff,
					      SDP_HDR_CONNECTION,
					      SDP_HDR_MEDIA,
					      &rtp_addr);
			if (ret != NF_ACCEPT) {
				nf_ct_helper_log(skb, ct, "cannot mangle SDP");
				return ret;
			}
		}
		i++;
	}

	/* Update session connection and owner addresses */
	hooks = rcu_dereference(nf_nat_sip_hooks);
	if (hooks && ct->status & IPS_NAT_MASK)
		ret = hooks->sdp_session(skb, protoff, dataoff,
					 dptr, datalen, sdpoff,
					 &rtp_addr);

	return ret;
}