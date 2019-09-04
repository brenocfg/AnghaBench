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
struct sip_handler {int (* response ) (struct sk_buff*,unsigned int,unsigned int,char const**,unsigned int*,unsigned int,unsigned int) ;unsigned int len; int /*<<< orphan*/  method; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct sip_handler*) ; 
 int NF_ACCEPT ; 
 int NF_DROP ; 
 int /*<<< orphan*/  SIP_HDR_CSEQ ; 
 scalar_t__ ct_sip_get_header (struct nf_conn*,char const*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_ct_helper_log (struct sk_buff*,struct nf_conn*,char*) ; 
 unsigned int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct sip_handler* sip_handlers ; 
 int strlen (char*) ; 
 scalar_t__ strncasecmp (char const*,int /*<<< orphan*/ ,unsigned int) ; 
 int stub1 (struct sk_buff*,unsigned int,unsigned int,char const**,unsigned int*,unsigned int,unsigned int) ; 

__attribute__((used)) static int process_sip_response(struct sk_buff *skb, unsigned int protoff,
				unsigned int dataoff,
				const char **dptr, unsigned int *datalen)
{
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	unsigned int matchoff, matchlen, matchend;
	unsigned int code, cseq, i;

	if (*datalen < strlen("SIP/2.0 200"))
		return NF_ACCEPT;
	code = simple_strtoul(*dptr + strlen("SIP/2.0 "), NULL, 10);
	if (!code) {
		nf_ct_helper_log(skb, ct, "cannot get code");
		return NF_DROP;
	}

	if (ct_sip_get_header(ct, *dptr, 0, *datalen, SIP_HDR_CSEQ,
			      &matchoff, &matchlen) <= 0) {
		nf_ct_helper_log(skb, ct, "cannot parse cseq");
		return NF_DROP;
	}
	cseq = simple_strtoul(*dptr + matchoff, NULL, 10);
	if (!cseq && *(*dptr + matchoff) != '0') {
		nf_ct_helper_log(skb, ct, "cannot get cseq");
		return NF_DROP;
	}
	matchend = matchoff + matchlen + 1;

	for (i = 0; i < ARRAY_SIZE(sip_handlers); i++) {
		const struct sip_handler *handler;

		handler = &sip_handlers[i];
		if (handler->response == NULL)
			continue;
		if (*datalen < matchend + handler->len ||
		    strncasecmp(*dptr + matchend, handler->method, handler->len))
			continue;
		return handler->response(skb, protoff, dataoff, dptr, datalen,
					 cseq, code);
	}
	return NF_ACCEPT;
}