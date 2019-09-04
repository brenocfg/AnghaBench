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
struct btf_type {int /*<<< orphan*/  info; } ;
struct btf_kind_operations {int dummy; } ;

/* Variables and functions */
 size_t BTF_INFO_KIND (int /*<<< orphan*/ ) ; 
 struct btf_kind_operations const** kind_ops ; 

__attribute__((used)) static const struct btf_kind_operations *btf_type_ops(const struct btf_type *t)
{
	return kind_ops[BTF_INFO_KIND(t->info)];
}