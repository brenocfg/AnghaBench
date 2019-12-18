#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
union sctp_addr {TYPE_2__ v4; } ;
struct flowi4 {int /*<<< orphan*/  saddr; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 

__attribute__((used)) static void sctp_v4_dst_saddr(union sctp_addr *saddr, struct flowi4 *fl4,
			      __be16 port)
{
	saddr->v4.sin_family = AF_INET;
	saddr->v4.sin_port = port;
	saddr->v4.sin_addr.s_addr = fl4->saddr;
}