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
struct nf_conn {int dummy; } ;

/* Variables and functions */
 char* ct_sip_header_search (char const*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sip_parse_addr (struct nf_conn const*,char const*,char const**,union nf_inet_addr*,char const*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int ct_sip_parse_address_param(const struct nf_conn *ct, const char *dptr,
			       unsigned int dataoff, unsigned int datalen,
			       const char *name,
			       unsigned int *matchoff, unsigned int *matchlen,
			       union nf_inet_addr *addr, bool delim)
{
	const char *limit = dptr + datalen;
	const char *start, *end;

	limit = ct_sip_header_search(dptr + dataoff, limit, ",", strlen(","));
	if (!limit)
		limit = dptr + datalen;

	start = ct_sip_header_search(dptr + dataoff, limit, name, strlen(name));
	if (!start)
		return 0;

	start += strlen(name);
	if (!sip_parse_addr(ct, start, &end, addr, limit, delim))
		return 0;
	*matchoff = start - dptr;
	*matchlen = end - start;
	return 1;
}