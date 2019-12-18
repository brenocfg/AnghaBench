#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct TYPE_2__ {struct sockaddr_in6 sin6; } ;
struct sockaddr_rxrpc {int transport_len; TYPE_1__ transport; int /*<<< orphan*/  transport_type; int /*<<< orphan*/  srx_family; } ;
struct afs_addr_list {int nr_addrs; int max_addrs; int nr_ipv4; struct sockaddr_rxrpc* addrs; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AF_RXRPC ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (struct sockaddr_rxrpc*,struct sockaddr_rxrpc*,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

void afs_merge_fs_addr6(struct afs_addr_list *alist, __be32 *xdr, u16 port)
{
	struct sockaddr_rxrpc *srx;
	int i, diff;

	if (alist->nr_addrs >= alist->max_addrs)
		return;

	for (i = alist->nr_ipv4; i < alist->nr_addrs; i++) {
		struct sockaddr_in6 *a = &alist->addrs[i].transport.sin6;
		u16 a_port = ntohs(a->sin6_port);

		diff = memcmp(xdr, &a->sin6_addr, 16);
		if (diff == 0 && port == a_port)
			return;
		if (diff == 0 && port < a_port)
			break;
		if (diff < 0)
			break;
	}

	if (i < alist->nr_addrs)
		memmove(alist->addrs + i + 1,
			alist->addrs + i,
			sizeof(alist->addrs[0]) * (alist->nr_addrs - i));

	srx = &alist->addrs[i];
	srx->srx_family = AF_RXRPC;
	srx->transport_type = SOCK_DGRAM;
	srx->transport_len = sizeof(srx->transport.sin6);
	srx->transport.sin6.sin6_family = AF_INET6;
	srx->transport.sin6.sin6_port = htons(port);
	memcpy(&srx->transport.sin6.sin6_addr, xdr, 16);
	alist->nr_addrs++;
}