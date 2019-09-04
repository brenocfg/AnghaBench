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
typedef  scalar_t__ u8 ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ ct_sip_parse_param (struct nf_conn*,char const*,unsigned int,unsigned int,char*,unsigned int*,unsigned int*) ; 
 scalar_t__ nf_ct_protonum (struct nf_conn*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ct_sip_parse_transport(struct nf_conn *ct, const char *dptr,
				  unsigned int dataoff, unsigned int datalen,
				  u8 *proto)
{
	unsigned int matchoff, matchlen;

	if (ct_sip_parse_param(ct, dptr, dataoff, datalen, "transport=",
			       &matchoff, &matchlen)) {
		if (!strncasecmp(dptr + matchoff, "TCP", strlen("TCP")))
			*proto = IPPROTO_TCP;
		else if (!strncasecmp(dptr + matchoff, "UDP", strlen("UDP")))
			*proto = IPPROTO_UDP;
		else
			return 0;

		if (*proto != nf_ct_protonum(ct))
			return 0;
	} else
		*proto = nf_ct_protonum(ct);

	return 1;
}