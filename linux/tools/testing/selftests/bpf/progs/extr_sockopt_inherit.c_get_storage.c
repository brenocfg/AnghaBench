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
struct sockopt_inherit {int dummy; } ;
struct bpf_sockopt {scalar_t__ optname; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_SK_STORAGE_GET_F_CREATE ; 
 scalar_t__ CUSTOM_INHERIT1 ; 
 scalar_t__ CUSTOM_INHERIT2 ; 
 struct sockopt_inherit* bpf_sk_storage_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cloned1_map ; 
 int /*<<< orphan*/  cloned2_map ; 
 int /*<<< orphan*/  listener_only_map ; 

__attribute__((used)) static __inline struct sockopt_inherit *get_storage(struct bpf_sockopt *ctx)
{
	if (ctx->optname == CUSTOM_INHERIT1)
		return bpf_sk_storage_get(&cloned1_map, ctx->sk, 0,
					  BPF_SK_STORAGE_GET_F_CREATE);
	else if (ctx->optname == CUSTOM_INHERIT2)
		return bpf_sk_storage_get(&cloned2_map, ctx->sk, 0,
					  BPF_SK_STORAGE_GET_F_CREATE);
	else
		return bpf_sk_storage_get(&listener_only_map, ctx->sk, 0,
					  BPF_SK_STORAGE_GET_F_CREATE);
}