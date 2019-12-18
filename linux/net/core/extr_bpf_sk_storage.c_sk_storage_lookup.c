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
struct sock {int /*<<< orphan*/  sk_bpf_storage; } ;
struct bpf_sk_storage_map {int dummy; } ;
struct bpf_sk_storage_data {int dummy; } ;
struct bpf_sk_storage {int dummy; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 struct bpf_sk_storage_data* __sk_storage_lookup (struct bpf_sk_storage*,struct bpf_sk_storage_map*,int) ; 
 struct bpf_sk_storage* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bpf_sk_storage_data *
sk_storage_lookup(struct sock *sk, struct bpf_map *map, bool cacheit_lockit)
{
	struct bpf_sk_storage *sk_storage;
	struct bpf_sk_storage_map *smap;

	sk_storage = rcu_dereference(sk->sk_bpf_storage);
	if (!sk_storage)
		return NULL;

	smap = (struct bpf_sk_storage_map *)map;
	return __sk_storage_lookup(sk_storage, smap, cacheit_lockit);
}