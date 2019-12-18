#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {int dummy; } ;
struct btf_type {int dummy; } ;
struct btf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* seq_show ) (struct btf const*,struct btf_type const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct seq_file*) ;} ;

/* Variables and functions */
 struct btf_type* btf_type_by_id (struct btf const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* btf_type_ops (struct btf_type const*) ; 
 int /*<<< orphan*/  stub1 (struct btf const*,struct btf_type const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct seq_file*) ; 

void btf_type_seq_show(const struct btf *btf, u32 type_id, void *obj,
		       struct seq_file *m)
{
	const struct btf_type *t = btf_type_by_id(btf, type_id);

	btf_type_ops(t)->seq_show(btf, t, type_id, obj, 0, m);
}