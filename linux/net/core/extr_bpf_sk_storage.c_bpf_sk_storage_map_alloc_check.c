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
union bpf_attr {int map_flags; int key_size; int value_size; int /*<<< orphan*/  btf_value_type_id; int /*<<< orphan*/  btf_key_type_id; scalar_t__ max_entries; } ;
struct bpf_sk_storage_elem {int dummy; } ;

/* Variables and functions */
 int BPF_F_NO_PREALLOC ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int E2BIG ; 
 int EINVAL ; 
 int EPERM ; 
 int KMALLOC_MAX_SIZE ; 
 int MAX_BPF_STACK ; 
 int SK_STORAGE_CREATE_FLAG_MASK ; 
 int U16_MAX ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_sk_storage_map_alloc_check(union bpf_attr *attr)
{
	if (attr->map_flags & ~SK_STORAGE_CREATE_FLAG_MASK ||
	    !(attr->map_flags & BPF_F_NO_PREALLOC) ||
	    attr->max_entries ||
	    attr->key_size != sizeof(int) || !attr->value_size ||
	    /* Enforce BTF for userspace sk dumping */
	    !attr->btf_key_type_id || !attr->btf_value_type_id)
		return -EINVAL;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	if (attr->value_size >= KMALLOC_MAX_SIZE -
	    MAX_BPF_STACK - sizeof(struct bpf_sk_storage_elem) ||
	    /* U16_MAX is much more than enough for sk local storage
	     * considering a tcp_sock is ~2k.
	     */
	    attr->value_size > U16_MAX - sizeof(struct bpf_sk_storage_elem))
		return -E2BIG;

	return 0;
}