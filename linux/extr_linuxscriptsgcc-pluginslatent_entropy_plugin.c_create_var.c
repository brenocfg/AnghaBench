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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  add_referenced_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_tmp_var (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mark_sym_for_renaming (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree create_var(tree type, const char *name)
{
	tree var;

	var = create_tmp_var(type, name);
	add_referenced_var(var);
	mark_sym_for_renaming(var);
	return var;
}