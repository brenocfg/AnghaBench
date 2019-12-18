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
typedef  scalar_t__ tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ATTRIBUTES (scalar_t__) ; 
 int RECORD_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 int UNION_TYPE ; 
 scalar_t__ get_field_type (scalar_t__) ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_userspace_type(tree type)
{
	tree field;

	for (field = TYPE_FIELDS(type); field; field = TREE_CHAIN(field)) {
		tree fieldtype = get_field_type(field);
		enum tree_code code = TREE_CODE(fieldtype);

		if (code == RECORD_TYPE || code == UNION_TYPE)
			if (is_userspace_type(fieldtype))
				return true;

		if (lookup_attribute("user", DECL_ATTRIBUTES(field)))
			return true;
	}
	return false;
}