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
typedef  int /*<<< orphan*/  u8 ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  BUG () ; 
 int in4_pton (char const*,int,int /*<<< orphan*/ *,int,char const**) ; 
 int in6_pton (char const*,int,int /*<<< orphan*/ *,int,char const**) ; 
 int /*<<< orphan*/  memset (union nf_inet_addr*,int /*<<< orphan*/ ,int) ; 
 int nf_ct_l3num (struct nf_conn const*) ; 

__attribute__((used)) static int sdp_parse_addr(const struct nf_conn *ct, const char *cp,
			  const char **endp, union nf_inet_addr *addr,
			  const char *limit)
{
	const char *end;
	int ret;

	memset(addr, 0, sizeof(*addr));
	switch (nf_ct_l3num(ct)) {
	case AF_INET:
		ret = in4_pton(cp, limit - cp, (u8 *)&addr->ip, -1, &end);
		break;
	case AF_INET6:
		ret = in6_pton(cp, limit - cp, (u8 *)&addr->ip6, -1, &end);
		break;
	default:
		BUG();
	}

	if (ret == 0)
		return 0;
	if (endp)
		*endp = end;
	return 1;
}