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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  scalar_t__ const_tree ;

/* Variables and functions */
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ UNION_TYPE ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_field_type (scalar_t__) ; 
 int /*<<< orphan*/  is_fptr (scalar_t__) ; 

__attribute__((used)) static int is_pure_ops_struct(const_tree node)
{
	const_tree field;

	gcc_assert(TREE_CODE(node) == RECORD_TYPE || TREE_CODE(node) == UNION_TYPE);

	for (field = TYPE_FIELDS(node); field; field = TREE_CHAIN(field)) {
		const_tree fieldtype = get_field_type(field);
		enum tree_code code = TREE_CODE(fieldtype);

		if (node == fieldtype)
			continue;

		if (code == RECORD_TYPE || code == UNION_TYPE) {
			if (!is_pure_ops_struct(fieldtype))
				return 0;
			continue;
		}

		if (!is_fptr(fieldtype))
			return 0;
	}

	return 1;
}