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
typedef  int u32 ;
typedef  int u16 ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  port ;
typedef  int /*<<< orphan*/  dst6 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ANY ; 
 int ENOENT ; 
 scalar_t__ PT_REGS_PARM2 (struct pt_regs*) ; 
 scalar_t__ PT_REGS_PARM3 (struct pt_regs*) ; 
 int /*<<< orphan*/  a_of_port_a ; 
 void* bpf_map_lookup_elem (void*,int*) ; 
 int /*<<< orphan*/  bpf_map_update_elem (int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ ) ; 
 int bpf_probe_read (int*,int,int /*<<< orphan*/ *) ; 
 int do_inline_array_lookup (void*,int) ; 
 int do_inline_hash_lookup (void*,int) ; 
 int do_reg_lookup (void*,int) ; 
 int /*<<< orphan*/  h_of_port_a ; 
 int /*<<< orphan*/  h_of_port_h ; 
 int /*<<< orphan*/  inline_result_h ; 
 int /*<<< orphan*/  reg_result_h ; 

int trace_sys_connect(struct pt_regs *ctx)
{
	struct sockaddr_in6 *in6;
	u16 test_case, port, dst6[8];
	int addrlen, ret, inline_ret, ret_key = 0;
	u32 port_key;
	void *outer_map, *inner_map;
	bool inline_hash = false;

	in6 = (struct sockaddr_in6 *)PT_REGS_PARM2(ctx);
	addrlen = (int)PT_REGS_PARM3(ctx);

	if (addrlen != sizeof(*in6))
		return 0;

	ret = bpf_probe_read(dst6, sizeof(dst6), &in6->sin6_addr);
	if (ret) {
		inline_ret = ret;
		goto done;
	}

	if (dst6[0] != 0xdead || dst6[1] != 0xbeef)
		return 0;

	test_case = dst6[7];

	ret = bpf_probe_read(&port, sizeof(port), &in6->sin6_port);
	if (ret) {
		inline_ret = ret;
		goto done;
	}

	port_key = port;

	ret = -ENOENT;
	if (test_case == 0) {
		outer_map = &a_of_port_a;
	} else if (test_case == 1) {
		outer_map = &h_of_port_a;
	} else if (test_case == 2) {
		outer_map = &h_of_port_h;
	} else {
		ret = __LINE__;
		inline_ret = ret;
		goto done;
	}

	inner_map = bpf_map_lookup_elem(outer_map, &port_key);
	if (!inner_map) {
		ret = __LINE__;
		inline_ret = ret;
		goto done;
	}

	ret = do_reg_lookup(inner_map, port_key);

	if (test_case == 0 || test_case == 1)
		inline_ret = do_inline_array_lookup(inner_map, port_key);
	else
		inline_ret = do_inline_hash_lookup(inner_map, port_key);

done:
	bpf_map_update_elem(&reg_result_h, &ret_key, &ret, BPF_ANY);
	bpf_map_update_elem(&inline_result_h, &ret_key, &inline_ret, BPF_ANY);

	return 0;
}