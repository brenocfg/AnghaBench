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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct xdp_exception_ctx {scalar_t__ act; } ;

/* Variables and functions */
 scalar_t__ XDP_REDIRECT ; 
 scalar_t__ XDP_UNKNOWN ; 
 int* bpf_map_lookup_elem (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  exception_cnt ; 

int trace_xdp_exception(struct xdp_exception_ctx *ctx)
{
	u64 *cnt;
	u32 key;

	key = ctx->act;
	if (key > XDP_REDIRECT)
		key = XDP_UNKNOWN;

	cnt = bpf_map_lookup_elem(&exception_cnt, &key);
	if (!cnt)
		return 1;
	*cnt += 1;

	return 0;
}