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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {int dummy; } ;
struct btf_type {int dummy; } ;
struct btf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* seq_show ) (struct btf const*,struct btf_type const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct seq_file*) ;} ;

/* Variables and functions */
 struct btf_type* btf_type_id_resolve (struct btf const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* btf_type_ops (struct btf_type const*) ; 
 int /*<<< orphan*/  stub1 (struct btf const*,struct btf_type const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct seq_file*) ; 

__attribute__((used)) static void btf_var_seq_show(const struct btf *btf, const struct btf_type *t,
			     u32 type_id, void *data, u8 bits_offset,
			     struct seq_file *m)
{
	t = btf_type_id_resolve(btf, &type_id);

	btf_type_ops(t)->seq_show(btf, t, type_id, data, bits_offset, m);
}