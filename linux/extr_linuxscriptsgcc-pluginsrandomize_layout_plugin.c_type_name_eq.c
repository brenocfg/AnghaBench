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
typedef  int /*<<< orphan*/  gimple ;
typedef  scalar_t__ const_tree ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR_TYPE_SIZE ; 
 int /*<<< orphan*/  INFORM (int /*<<< orphan*/ ,char*,scalar_t__) ; 
#define  INTEGER_TYPE 130 
 scalar_t__ NULL_TREE ; 
#define  POINTER_TYPE 129 
#define  RECORD_TYPE 128 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 char* TYPE_NAME_POINTER (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_PRECISION (scalar_t__) ; 
 int VOID_TYPE ; 
 int /*<<< orphan*/  debug_tree (scalar_t__) ; 
 int /*<<< orphan*/  gimple_location (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static bool type_name_eq(gimple stmt, const_tree type_tree, const char *wanted_name)
{
	const char *type_name;

	if (type_tree == NULL_TREE)
		return false;

	switch (TREE_CODE(type_tree)) {
	case RECORD_TYPE:
		type_name = TYPE_NAME_POINTER(type_tree);
		break;
	case INTEGER_TYPE:
		if (TYPE_PRECISION(type_tree) == CHAR_TYPE_SIZE)
			type_name = "char";
		else {
			INFORM(gimple_location(stmt), "found non-char INTEGER_TYPE cast comparison: %qT\n", type_tree);
			debug_tree(type_tree);
			return false;
		}
		break;
	case POINTER_TYPE:
		if (TREE_CODE(TREE_TYPE(type_tree)) == VOID_TYPE) {
			type_name = "void *";
			break;
		} else {
			INFORM(gimple_location(stmt), "found non-void POINTER_TYPE cast comparison %qT\n", type_tree);
			debug_tree(type_tree);
			return false;
		}
	default:
		INFORM(gimple_location(stmt), "unhandled cast comparison: %qT\n", type_tree);
		debug_tree(type_tree);
		return false;
	}

	return strcmp(type_name, wanted_name) == 0;
}