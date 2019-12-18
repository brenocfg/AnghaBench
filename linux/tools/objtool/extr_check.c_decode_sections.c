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
struct objtool_file {int dummy; } ;

/* Variables and functions */
 int add_call_destinations (struct objtool_file*) ; 
 int add_dead_ends (struct objtool_file*) ; 
 int add_ignore_alternatives (struct objtool_file*) ; 
 int /*<<< orphan*/  add_ignores (struct objtool_file*) ; 
 int add_jump_destinations (struct objtool_file*) ; 
 int add_jump_table_alts (struct objtool_file*) ; 
 int add_special_section_alts (struct objtool_file*) ; 
 int /*<<< orphan*/  add_uaccess_safe (struct objtool_file*) ; 
 int decode_instructions (struct objtool_file*) ; 
 int /*<<< orphan*/  mark_rodata (struct objtool_file*) ; 
 int read_retpoline_hints (struct objtool_file*) ; 
 int read_unwind_hints (struct objtool_file*) ; 

__attribute__((used)) static int decode_sections(struct objtool_file *file)
{
	int ret;

	mark_rodata(file);

	ret = decode_instructions(file);
	if (ret)
		return ret;

	ret = add_dead_ends(file);
	if (ret)
		return ret;

	add_ignores(file);
	add_uaccess_safe(file);

	ret = add_ignore_alternatives(file);
	if (ret)
		return ret;

	ret = add_jump_destinations(file);
	if (ret)
		return ret;

	ret = add_special_section_alts(file);
	if (ret)
		return ret;

	ret = add_call_destinations(file);
	if (ret)
		return ret;

	ret = add_jump_table_alts(file);
	if (ret)
		return ret;

	ret = read_unwind_hints(file);
	if (ret)
		return ret;

	ret = read_retpoline_hints(file);
	if (ret)
		return ret;

	return 0;
}