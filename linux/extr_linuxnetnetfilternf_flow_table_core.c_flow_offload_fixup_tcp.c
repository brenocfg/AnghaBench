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
struct ip_ct_tcp {TYPE_1__* seen; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {scalar_t__ td_maxwin; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_CONNTRACK_ESTABLISHED ; 

__attribute__((used)) static void flow_offload_fixup_tcp(struct ip_ct_tcp *tcp)
{
	tcp->state = TCP_CONNTRACK_ESTABLISHED;
	tcp->seen[0].td_maxwin = 0;
	tcp->seen[1].td_maxwin = 0;
}