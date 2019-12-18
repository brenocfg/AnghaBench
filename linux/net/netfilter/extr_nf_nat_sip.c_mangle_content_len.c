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
struct sk_buff {int dummy; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int /*<<< orphan*/  SDP_HDR_UNSPEC ; 
 int /*<<< orphan*/  SDP_HDR_VERSION ; 
 int /*<<< orphan*/  SIP_HDR_CONTENT_LENGTH ; 
 scalar_t__ ct_sip_get_header (struct nf_conn*,char const*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 scalar_t__ ct_sip_get_sdp_header (struct nf_conn*,char const*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int mangle_packet (struct sk_buff*,unsigned int,unsigned int,char const**,unsigned int*,unsigned int,unsigned int,char*,int) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int sprintf (char*,char*,int) ; 
 unsigned int strlen (char*) ; 

__attribute__((used)) static int mangle_content_len(struct sk_buff *skb, unsigned int protoff,
			      unsigned int dataoff,
			      const char **dptr, unsigned int *datalen)
{
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	unsigned int matchoff, matchlen;
	char buffer[sizeof("65536")];
	int buflen, c_len;

	/* Get actual SDP length */
	if (ct_sip_get_sdp_header(ct, *dptr, 0, *datalen,
				  SDP_HDR_VERSION, SDP_HDR_UNSPEC,
				  &matchoff, &matchlen) <= 0)
		return 0;
	c_len = *datalen - matchoff + strlen("v=");

	/* Now, update SDP length */
	if (ct_sip_get_header(ct, *dptr, 0, *datalen, SIP_HDR_CONTENT_LENGTH,
			      &matchoff, &matchlen) <= 0)
		return 0;

	buflen = sprintf(buffer, "%u", c_len);
	return mangle_packet(skb, protoff, dataoff, dptr, datalen,
			     matchoff, matchlen, buffer, buflen);
}