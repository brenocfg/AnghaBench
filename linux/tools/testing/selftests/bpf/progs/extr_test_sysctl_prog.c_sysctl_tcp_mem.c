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
struct bpf_sysctl {scalar_t__ write; } ;

/* Variables and functions */
 unsigned char ARRAY_SIZE (unsigned long*) ; 
 int MAX_ULONG_STR_LEN ; 
 int MAX_VALUE_STR_LEN ; 
 int bpf_strtoul (char*,int,int /*<<< orphan*/ ,unsigned long*) ; 
 int bpf_sysctl_get_current_value (struct bpf_sysctl*,char*,int) ; 
 int /*<<< orphan*/  is_tcp_mem (struct bpf_sysctl*) ; 

int sysctl_tcp_mem(struct bpf_sysctl *ctx)
{
	unsigned long tcp_mem[3] = {0, 0, 0};
	char value[MAX_VALUE_STR_LEN];
	unsigned char i, off = 0;
	int ret;

	if (ctx->write)
		return 0;

	if (!is_tcp_mem(ctx))
		return 0;

	ret = bpf_sysctl_get_current_value(ctx, value, MAX_VALUE_STR_LEN);
	if (ret < 0 || ret >= MAX_VALUE_STR_LEN)
		return 0;

#pragma clang loop unroll(full)
	for (i = 0; i < ARRAY_SIZE(tcp_mem); ++i) {
		ret = bpf_strtoul(value + off, MAX_ULONG_STR_LEN, 0,
				  tcp_mem + i);
		if (ret <= 0 || ret > MAX_ULONG_STR_LEN)
			return 0;
		off += ret & MAX_ULONG_STR_LEN;
	}


	return tcp_mem[0] < tcp_mem[1] && tcp_mem[1] < tcp_mem[2];
}