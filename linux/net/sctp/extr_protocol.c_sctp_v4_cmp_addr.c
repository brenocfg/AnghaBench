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
struct TYPE_5__ {scalar_t__ s_addr; } ;
struct TYPE_6__ {scalar_t__ sin_port; TYPE_2__ sin_addr; } ;
struct TYPE_4__ {scalar_t__ sa_family; } ;
union sctp_addr {TYPE_3__ v4; TYPE_1__ sa; } ;

/* Variables and functions */

__attribute__((used)) static int sctp_v4_cmp_addr(const union sctp_addr *addr1,
			    const union sctp_addr *addr2)
{
	if (addr1->sa.sa_family != addr2->sa.sa_family)
		return 0;
	if (addr1->v4.sin_port != addr2->v4.sin_port)
		return 0;
	if (addr1->v4.sin_addr.s_addr != addr2->v4.sin_addr.s_addr)
		return 0;

	return 1;
}