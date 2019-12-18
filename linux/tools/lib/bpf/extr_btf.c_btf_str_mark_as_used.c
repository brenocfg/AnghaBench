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
struct btf_str_ptrs {scalar_t__ data; int /*<<< orphan*/  cnt; int /*<<< orphan*/  ptrs; } ;
struct btf_str_ptr {int used; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int EINVAL ; 
 struct btf_str_ptr* bsearch (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btf_dedup_str_ptr_cmp ; 

__attribute__((used)) static int btf_str_mark_as_used(__u32 *str_off_ptr, void *ctx)
{
	struct btf_str_ptrs *strs;
	struct btf_str_ptr *s;

	if (*str_off_ptr == 0)
		return 0;

	strs = ctx;
	s = bsearch(strs->data + *str_off_ptr, strs->ptrs, strs->cnt,
		    sizeof(struct btf_str_ptr), btf_dedup_str_ptr_cmp);
	if (!s)
		return -EINVAL;
	s->used = true;
	return 0;
}