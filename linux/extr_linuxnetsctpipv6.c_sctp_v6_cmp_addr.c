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
struct TYPE_2__ {scalar_t__ sin6_port; } ;
union sctp_addr {TYPE_1__ v6; } ;

/* Variables and functions */
 scalar_t__ __sctp_v6_cmp_addr (union sctp_addr const*,union sctp_addr const*) ; 

__attribute__((used)) static int sctp_v6_cmp_addr(const union sctp_addr *addr1,
			    const union sctp_addr *addr2)
{
	return __sctp_v6_cmp_addr(addr1, addr2) &&
	       addr1->v6.sin6_port == addr2->v6.sin6_port;
}