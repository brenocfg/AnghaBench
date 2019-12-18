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
typedef  scalar_t__ const_tree ;

/* Variables and functions */
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_CONSTANT (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_DOMAIN (scalar_t__) ; 
 scalar_t__ TYPE_MAX_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_SIZE (scalar_t__) ; 
 scalar_t__ tree_to_uhwi (scalar_t__) ; 

__attribute__((used)) static bool is_flexible_array(const_tree field)
{
	const_tree fieldtype;
	const_tree typesize;
	const_tree elemtype;
	const_tree elemsize;

	fieldtype = TREE_TYPE(field);
	typesize = TYPE_SIZE(fieldtype);

	if (TREE_CODE(fieldtype) != ARRAY_TYPE)
		return false;

	elemtype = TREE_TYPE(fieldtype);
	elemsize = TYPE_SIZE(elemtype);

	/* size of type is represented in bits */

	if (typesize == NULL_TREE && TYPE_DOMAIN(fieldtype) != NULL_TREE &&
	    TYPE_MAX_VALUE(TYPE_DOMAIN(fieldtype)) == NULL_TREE)
		return true;

	if (typesize != NULL_TREE &&
	    (TREE_CONSTANT(typesize) && (!tree_to_uhwi(typesize) ||
	     tree_to_uhwi(typesize) == tree_to_uhwi(elemsize))))
		return true;

	return false;
}