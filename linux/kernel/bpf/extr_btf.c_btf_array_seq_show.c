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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct seq_file {int dummy; } ;
struct btf_type {int dummy; } ;
struct btf_kind_operations {int /*<<< orphan*/  (* seq_show ) (struct btf const*,struct btf_type const*,scalar_t__,void*,int /*<<< orphan*/ ,struct seq_file*) ;} ;
struct btf_array {scalar_t__ type; scalar_t__ nelems; } ;
struct btf {int dummy; } ;

/* Variables and functions */
 struct btf_array* btf_type_array (struct btf_type const*) ; 
 struct btf_type* btf_type_id_size (struct btf const*,scalar_t__*,scalar_t__*) ; 
 struct btf_kind_operations* btf_type_ops (struct btf_type const*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  stub1 (struct btf const*,struct btf_type const*,scalar_t__,void*,int /*<<< orphan*/ ,struct seq_file*) ; 

__attribute__((used)) static void btf_array_seq_show(const struct btf *btf, const struct btf_type *t,
			       u32 type_id, void *data, u8 bits_offset,
			       struct seq_file *m)
{
	const struct btf_array *array = btf_type_array(t);
	const struct btf_kind_operations *elem_ops;
	const struct btf_type *elem_type;
	u32 i, elem_size, elem_type_id;

	elem_type_id = array->type;
	elem_type = btf_type_id_size(btf, &elem_type_id, &elem_size);
	elem_ops = btf_type_ops(elem_type);
	seq_puts(m, "[");
	for (i = 0; i < array->nelems; i++) {
		if (i)
			seq_puts(m, ",");

		elem_ops->seq_show(btf, elem_type, elem_type_id, data,
				   bits_offset, m);
		data += elem_size;
	}
	seq_puts(m, "]");
}