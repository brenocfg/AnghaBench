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
struct xdr_stream {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int sa_family; } ;
struct nfs4_pnfs_ds_addr {int /*<<< orphan*/  da_addr; } ;
typedef  int /*<<< orphan*/  portbuf ;
typedef  int /*<<< orphan*/  addrbuf ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int RPCBIND_MAXUADDRLEN ; 
 int RPCBIND_MAXUADDRPLEN ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ff_layout_ntop4 (struct sockaddr*,char*,int) ; 
 int /*<<< orphan*/  ff_layout_ntop6_noscopeid (struct sockaddr*,char*,int) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned short,unsigned short) ; 
 int strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  xdr_encode_opaque (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void
ff_layout_encode_netaddr(struct xdr_stream *xdr, struct nfs4_pnfs_ds_addr *da)
{
	struct sockaddr *sap = (struct sockaddr *)&da->da_addr;
	char portbuf[RPCBIND_MAXUADDRPLEN];
	char addrbuf[RPCBIND_MAXUADDRLEN];
	char *netid;
	unsigned short port;
	int len, netid_len;
	__be32 *p;

	switch (sap->sa_family) {
	case AF_INET:
		if (ff_layout_ntop4(sap, addrbuf, sizeof(addrbuf)) == 0)
			return;
		port = ntohs(((struct sockaddr_in *)sap)->sin_port);
		netid = "tcp";
		netid_len = 3;
		break;
	case AF_INET6:
		if (ff_layout_ntop6_noscopeid(sap, addrbuf, sizeof(addrbuf)) == 0)
			return;
		port = ntohs(((struct sockaddr_in6 *)sap)->sin6_port);
		netid = "tcp6";
		netid_len = 4;
		break;
	default:
		/* we only support tcp and tcp6 */
		WARN_ON_ONCE(1);
		return;
	}

	snprintf(portbuf, sizeof(portbuf), ".%u.%u", port >> 8, port & 0xff);
	len = strlcat(addrbuf, portbuf, sizeof(addrbuf));

	p = xdr_reserve_space(xdr, 4 + netid_len);
	xdr_encode_opaque(p, netid, netid_len);

	p = xdr_reserve_space(xdr, 4 + len);
	xdr_encode_opaque(p, addrbuf, len);
}