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
union nf_inet_addr {int /*<<< orphan*/  ip6; int /*<<< orphan*/  ip; } ;
typedef  int u16 ;
struct nf_conn {int dummy; } ;
typedef  enum nf_ct_ftp_type { ____Placeholder_nf_ct_ftp_type } nf_ct_ftp_type ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
#define  NF_CT_FTP_EPRT 131 
#define  NF_CT_FTP_EPSV 130 
#define  NF_CT_FTP_PASV 129 
#define  NF_CT_FTP_PORT 128 
 int /*<<< orphan*/  nf_ct_l3num (struct nf_conn*) ; 
 int snprintf (char*,size_t,char*,int,...) ; 

__attribute__((used)) static int nf_nat_ftp_fmt_cmd(struct nf_conn *ct, enum nf_ct_ftp_type type,
			      char *buffer, size_t buflen,
			      union nf_inet_addr *addr, u16 port)
{
	switch (type) {
	case NF_CT_FTP_PORT:
	case NF_CT_FTP_PASV:
		return snprintf(buffer, buflen, "%u,%u,%u,%u,%u,%u",
				((unsigned char *)&addr->ip)[0],
				((unsigned char *)&addr->ip)[1],
				((unsigned char *)&addr->ip)[2],
				((unsigned char *)&addr->ip)[3],
				port >> 8,
				port & 0xFF);
	case NF_CT_FTP_EPRT:
		if (nf_ct_l3num(ct) == NFPROTO_IPV4)
			return snprintf(buffer, buflen, "|1|%pI4|%u|",
					&addr->ip, port);
		else
			return snprintf(buffer, buflen, "|2|%pI6|%u|",
					&addr->ip6, port);
	case NF_CT_FTP_EPSV:
		return snprintf(buffer, buflen, "|||%u|", port);
	}

	return 0;
}