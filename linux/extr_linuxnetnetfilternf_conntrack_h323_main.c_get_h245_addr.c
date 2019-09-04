#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct nf_conn {int dummy; } ;
typedef  union nf_inet_addr __be16 ;
struct TYPE_7__ {int /*<<< orphan*/  network; } ;
struct TYPE_6__ {int /*<<< orphan*/  network; } ;
struct TYPE_8__ {int choice; TYPE_2__ iP6Address; TYPE_1__ iPAddress; } ;
struct TYPE_9__ {scalar_t__ choice; TYPE_3__ unicastAddress; } ;
typedef  TYPE_4__ H245_TransportAddress ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ eH245_TransportAddress_unicastAddress ; 
#define  eUnicastAddress_iP6Address 129 
#define  eUnicastAddress_iPAddress 128 
 int /*<<< orphan*/  memcpy (union nf_inet_addr*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_ct_l3num (struct nf_conn*) ; 

__attribute__((used)) static int get_h245_addr(struct nf_conn *ct, const unsigned char *data,
			 H245_TransportAddress *taddr,
			 union nf_inet_addr *addr, __be16 *port)
{
	const unsigned char *p;
	int len;

	if (taddr->choice != eH245_TransportAddress_unicastAddress)
		return 0;

	switch (taddr->unicastAddress.choice) {
	case eUnicastAddress_iPAddress:
		if (nf_ct_l3num(ct) != AF_INET)
			return 0;
		p = data + taddr->unicastAddress.iPAddress.network;
		len = 4;
		break;
	case eUnicastAddress_iP6Address:
		if (nf_ct_l3num(ct) != AF_INET6)
			return 0;
		p = data + taddr->unicastAddress.iP6Address.network;
		len = 16;
		break;
	default:
		return 0;
	}

	memcpy(addr, p, len);
	memset((void *)addr + len, 0, sizeof(*addr) - len);
	memcpy(port, p + len, sizeof(__be16));

	return 1;
}