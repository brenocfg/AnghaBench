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
typedef  int /*<<< orphan*/  const_tree ;

/* Variables and functions */
 scalar_t__ DECL_SECTION_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 char const* TREE_STRING_POINTER (scalar_t__) ; 

__attribute__((used)) static inline const char *get_decl_section_name(const_tree decl)
{
	if (DECL_SECTION_NAME(decl) == NULL_TREE)
		return NULL;

	return TREE_STRING_POINTER(DECL_SECTION_NAME(decl));
}