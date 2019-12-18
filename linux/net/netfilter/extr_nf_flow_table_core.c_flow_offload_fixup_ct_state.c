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
struct TYPE_2__ {int /*<<< orphan*/  tcp; } ;
struct nf_conn {TYPE_1__ proto; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  flow_offload_fixup_tcp (int /*<<< orphan*/ *) ; 
 scalar_t__ nf_ct_protonum (struct nf_conn*) ; 

__attribute__((used)) static void flow_offload_fixup_ct_state(struct nf_conn *ct)
{
	if (nf_ct_protonum(ct) == IPPROTO_TCP)
		flow_offload_fixup_tcp(&ct->proto.tcp);
}