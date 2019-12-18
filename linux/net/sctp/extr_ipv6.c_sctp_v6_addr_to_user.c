#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sin_zero; } ;
struct TYPE_6__ {scalar_t__ sa_family; } ;
struct TYPE_5__ {int /*<<< orphan*/  sin6_addr; } ;
union sctp_addr {TYPE_1__ v4; TYPE_3__ sa; TYPE_2__ v6; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sctp_sock {scalar_t__ v4mapped; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ ipv6_addr_v4mapped (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sctp_v4_map_v6 (union sctp_addr*) ; 
 int /*<<< orphan*/  sctp_v6_map_v4 (union sctp_addr*) ; 

__attribute__((used)) static int sctp_v6_addr_to_user(struct sctp_sock *sp, union sctp_addr *addr)
{
	if (sp->v4mapped) {
		if (addr->sa.sa_family == AF_INET)
			sctp_v4_map_v6(addr);
	} else {
		if (addr->sa.sa_family == AF_INET6 &&
		    ipv6_addr_v4mapped(&addr->v6.sin6_addr))
			sctp_v6_map_v4(addr);
	}

	if (addr->sa.sa_family == AF_INET) {
		memset(addr->v4.sin_zero, 0, sizeof(addr->v4.sin_zero));
		return sizeof(struct sockaddr_in);
	}
	return sizeof(struct sockaddr_in6);
}