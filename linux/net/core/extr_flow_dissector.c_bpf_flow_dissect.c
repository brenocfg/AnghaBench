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
typedef  scalar_t__ u32 ;
struct bpf_prog {int dummy; } ;
struct bpf_flow_keys {int nhoff; int thoff; unsigned int flags; int /*<<< orphan*/  n_proto; } ;
struct bpf_flow_dissector {struct bpf_flow_keys* flow_keys; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ BPF_FLOW_DISSECTOR_F_PARSE_1ST_FRAG ; 
 scalar_t__ BPF_FLOW_DISSECTOR_F_STOP_AT_ENCAP ; 
 scalar_t__ BPF_FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL ; 
 scalar_t__ BPF_OK ; 
 scalar_t__ BPF_PROG_RUN (struct bpf_prog*,struct bpf_flow_dissector*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ FLOW_DISSECTOR_F_PARSE_1ST_FRAG ; 
 scalar_t__ FLOW_DISSECTOR_F_STOP_AT_ENCAP ; 
 scalar_t__ FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL ; 
 void* clamp_t (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  memset (struct bpf_flow_keys*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  u16 ; 

bool bpf_flow_dissect(struct bpf_prog *prog, struct bpf_flow_dissector *ctx,
		      __be16 proto, int nhoff, int hlen, unsigned int flags)
{
	struct bpf_flow_keys *flow_keys = ctx->flow_keys;
	u32 result;

	/* Pass parameters to the BPF program */
	memset(flow_keys, 0, sizeof(*flow_keys));
	flow_keys->n_proto = proto;
	flow_keys->nhoff = nhoff;
	flow_keys->thoff = flow_keys->nhoff;

	BUILD_BUG_ON((int)BPF_FLOW_DISSECTOR_F_PARSE_1ST_FRAG !=
		     (int)FLOW_DISSECTOR_F_PARSE_1ST_FRAG);
	BUILD_BUG_ON((int)BPF_FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL !=
		     (int)FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL);
	BUILD_BUG_ON((int)BPF_FLOW_DISSECTOR_F_STOP_AT_ENCAP !=
		     (int)FLOW_DISSECTOR_F_STOP_AT_ENCAP);
	flow_keys->flags = flags;

	preempt_disable();
	result = BPF_PROG_RUN(prog, ctx);
	preempt_enable();

	flow_keys->nhoff = clamp_t(u16, flow_keys->nhoff, nhoff, hlen);
	flow_keys->thoff = clamp_t(u16, flow_keys->thoff,
				   flow_keys->nhoff, hlen);

	return result == BPF_OK;
}