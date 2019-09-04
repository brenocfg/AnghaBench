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
union nf_inet_addr {int ip; int /*<<< orphan*/  in6; } ;

/* Variables and functions */
#define  NFPROTO_IPV4 129 
#define  NFPROTO_IPV6 128 
 int /*<<< orphan*/  ipv6_masked_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
xt_addr_cmp(const union nf_inet_addr *a1, const union nf_inet_addr *m,
	    const union nf_inet_addr *a2, unsigned short family)
{
	switch (family) {
	case NFPROTO_IPV4:
		return ((a1->ip ^ a2->ip) & m->ip) == 0;
	case NFPROTO_IPV6:
		return ipv6_masked_addr_cmp(&a1->in6, &m->in6, &a2->in6) == 0;
	}
	return false;
}