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
union bpf_attr {int /*<<< orphan*/  btf_log_size; int /*<<< orphan*/  btf_log_buf; int /*<<< orphan*/  btf_log_level; int /*<<< orphan*/  btf_size; int /*<<< orphan*/  btf; } ;
struct btf {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct btf*) ; 
 int PTR_ERR (struct btf*) ; 
 int __btf_new_fd (struct btf*) ; 
 int btf_alloc_id (struct btf*) ; 
 int /*<<< orphan*/  btf_free (struct btf*) ; 
 struct btf* btf_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btf_put (struct btf*) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 

int btf_new_fd(const union bpf_attr *attr)
{
	struct btf *btf;
	int ret;

	btf = btf_parse(u64_to_user_ptr(attr->btf),
			attr->btf_size, attr->btf_log_level,
			u64_to_user_ptr(attr->btf_log_buf),
			attr->btf_log_size);
	if (IS_ERR(btf))
		return PTR_ERR(btf);

	ret = btf_alloc_id(btf);
	if (ret) {
		btf_free(btf);
		return ret;
	}

	/*
	 * The BTF ID is published to the userspace.
	 * All BTF free must go through call_rcu() from
	 * now on (i.e. free by calling btf_put()).
	 */

	ret = __btf_new_fd(btf);
	if (ret < 0)
		btf_put(btf);

	return ret;
}