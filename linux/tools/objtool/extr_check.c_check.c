#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int hints; int /*<<< orphan*/  elf; int /*<<< orphan*/  insn_list; int /*<<< orphan*/  ignore_unreachables; int /*<<< orphan*/  c_file; int /*<<< orphan*/  insn_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  arch_initial_func_cfi_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup (TYPE_1__*) ; 
 int create_orc (TYPE_1__*) ; 
 int create_orc_sections (TYPE_1__*) ; 
 int decode_sections (TYPE_1__*) ; 
 int /*<<< orphan*/  elf_read (char const*,int /*<<< orphan*/ ) ; 
 int elf_write (int /*<<< orphan*/ ) ; 
 TYPE_1__ file ; 
 int /*<<< orphan*/  find_section_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initial_func_cfi ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  no_unreachable ; 
 char const* objname ; 
 scalar_t__ retpoline ; 
 int validate_functions (TYPE_1__*) ; 
 int validate_reachable_instructions (TYPE_1__*) ; 
 int validate_retpoline (TYPE_1__*) ; 
 int validate_unwind_hints (TYPE_1__*) ; 

int check(const char *_objname, bool orc)
{
	int ret, warnings = 0;

	objname = _objname;

	file.elf = elf_read(objname, orc ? O_RDWR : O_RDONLY);
	if (!file.elf)
		return 1;

	INIT_LIST_HEAD(&file.insn_list);
	hash_init(file.insn_hash);
	file.c_file = find_section_by_name(file.elf, ".comment");
	file.ignore_unreachables = no_unreachable;
	file.hints = false;

	arch_initial_func_cfi_state(&initial_func_cfi);

	ret = decode_sections(&file);
	if (ret < 0)
		goto out;
	warnings += ret;

	if (list_empty(&file.insn_list))
		goto out;

	if (retpoline) {
		ret = validate_retpoline(&file);
		if (ret < 0)
			return ret;
		warnings += ret;
	}

	ret = validate_functions(&file);
	if (ret < 0)
		goto out;
	warnings += ret;

	ret = validate_unwind_hints(&file);
	if (ret < 0)
		goto out;
	warnings += ret;

	if (!warnings) {
		ret = validate_reachable_instructions(&file);
		if (ret < 0)
			goto out;
		warnings += ret;
	}

	if (orc) {
		ret = create_orc(&file);
		if (ret < 0)
			goto out;

		ret = create_orc_sections(&file);
		if (ret < 0)
			goto out;

		ret = elf_write(file.elf);
		if (ret < 0)
			goto out;
	}

out:
	cleanup(&file);

	/* ignore warnings for now until we get all the code cleaned up */
	if (ret || warnings)
		return 0;
	return 0;
}