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
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flow_offload_fixup_ct_state (struct nf_conn*) ; 
 int /*<<< orphan*/  flow_offload_fixup_ct_timeout (struct nf_conn*) ; 

__attribute__((used)) static void flow_offload_fixup_ct(struct nf_conn *ct)
{
	flow_offload_fixup_ct_state(ct);
	flow_offload_fixup_ct_timeout(ct);
}