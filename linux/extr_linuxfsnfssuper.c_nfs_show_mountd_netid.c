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
struct sockaddr {int sa_family; } ;
struct seq_file {int dummy; } ;
struct nfs_server {int /*<<< orphan*/  mountd_protocol; int /*<<< orphan*/  mountd_address; } ;

/* Variables and functions */
#define  AF_INET 131 
#define  AF_INET6 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 char* RPCBIND_NETID_TCP ; 
 char* RPCBIND_NETID_TCP6 ; 
 char* RPCBIND_NETID_UDP ; 
 char* RPCBIND_NETID_UDP6 ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 

__attribute__((used)) static void nfs_show_mountd_netid(struct seq_file *m, struct nfs_server *nfss,
				  int showdefaults)
{
	struct sockaddr *sap = (struct sockaddr *) &nfss->mountd_address;
	char *proto = NULL;

	switch (sap->sa_family) {
	case AF_INET:
		switch (nfss->mountd_protocol) {
		case IPPROTO_UDP:
			proto = RPCBIND_NETID_UDP;
			break;
		case IPPROTO_TCP:
			proto = RPCBIND_NETID_TCP;
			break;
		}
		break;
	case AF_INET6:
		switch (nfss->mountd_protocol) {
		case IPPROTO_UDP:
			proto = RPCBIND_NETID_UDP6;
			break;
		case IPPROTO_TCP:
			proto = RPCBIND_NETID_TCP6;
			break;
		}
		break;
	}
	if (proto || showdefaults)
		seq_printf(m, ",mountproto=%s", proto ?: "auto");
}