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
typedef  enum bpf_func_id { ____Placeholder_bpf_func_id } bpf_func_id ;

/* Variables and functions */
 int BPF_FUNC_sk_lookup_tcp ; 
 int BPF_FUNC_sk_lookup_udp ; 
 int BPF_FUNC_skc_lookup_tcp ; 

__attribute__((used)) static bool is_acquire_function(enum bpf_func_id func_id)
{
	return func_id == BPF_FUNC_sk_lookup_tcp ||
		func_id == BPF_FUNC_sk_lookup_udp ||
		func_id == BPF_FUNC_skc_lookup_tcp;
}