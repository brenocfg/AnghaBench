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
struct TYPE_6__ {scalar_t__ s_addr; } ;
struct TYPE_5__ {TYPE_3__ sin_addr; } ;
struct TYPE_4__ {scalar_t__ sa_family; } ;
union sctp_addr {TYPE_2__ v4; TYPE_1__ sa; } ;
struct sctp_sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sctp_inet_cmp_addr(const union sctp_addr *addr1,
			      const union sctp_addr *addr2,
			      struct sctp_sock *opt)
{
	/* PF_INET only supports AF_INET addresses. */
	if (addr1->sa.sa_family != addr2->sa.sa_family)
		return 0;
	if (htonl(INADDR_ANY) == addr1->v4.sin_addr.s_addr ||
	    htonl(INADDR_ANY) == addr2->v4.sin_addr.s_addr)
		return 1;
	if (addr1->v4.sin_addr.s_addr == addr2->v4.sin_addr.s_addr)
		return 1;

	return 0;
}