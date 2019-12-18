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
struct bpf_verifier_env {scalar_t__ strict_alignment; } ;
struct bpf_reg_state {int type; } ;

/* Variables and functions */
#define  PTR_TO_CTX 137 
#define  PTR_TO_FLOW_KEYS 136 
#define  PTR_TO_MAP_VALUE 135 
#define  PTR_TO_PACKET 134 
#define  PTR_TO_PACKET_META 133 
#define  PTR_TO_SOCKET 132 
#define  PTR_TO_SOCK_COMMON 131 
#define  PTR_TO_STACK 130 
#define  PTR_TO_TCP_SOCK 129 
#define  PTR_TO_XDP_SOCK 128 
 int check_generic_ptr_alignment (struct bpf_verifier_env*,struct bpf_reg_state const*,char const*,int,int,int) ; 
 int check_pkt_ptr_alignment (struct bpf_verifier_env*,struct bpf_reg_state const*,int,int,int) ; 

__attribute__((used)) static int check_ptr_alignment(struct bpf_verifier_env *env,
			       const struct bpf_reg_state *reg, int off,
			       int size, bool strict_alignment_once)
{
	bool strict = env->strict_alignment || strict_alignment_once;
	const char *pointer_desc = "";

	switch (reg->type) {
	case PTR_TO_PACKET:
	case PTR_TO_PACKET_META:
		/* Special case, because of NET_IP_ALIGN. Given metadata sits
		 * right in front, treat it the very same way.
		 */
		return check_pkt_ptr_alignment(env, reg, off, size, strict);
	case PTR_TO_FLOW_KEYS:
		pointer_desc = "flow keys ";
		break;
	case PTR_TO_MAP_VALUE:
		pointer_desc = "value ";
		break;
	case PTR_TO_CTX:
		pointer_desc = "context ";
		break;
	case PTR_TO_STACK:
		pointer_desc = "stack ";
		/* The stack spill tracking logic in check_stack_write()
		 * and check_stack_read() relies on stack accesses being
		 * aligned.
		 */
		strict = true;
		break;
	case PTR_TO_SOCKET:
		pointer_desc = "sock ";
		break;
	case PTR_TO_SOCK_COMMON:
		pointer_desc = "sock_common ";
		break;
	case PTR_TO_TCP_SOCK:
		pointer_desc = "tcp_sock ";
		break;
	case PTR_TO_XDP_SOCK:
		pointer_desc = "xdp_sock ";
		break;
	default:
		break;
	}
	return check_generic_ptr_alignment(env, reg, pointer_desc, off, size,
					   strict);
}