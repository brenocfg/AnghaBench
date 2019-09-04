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
struct linux_binprm {int interp_flags; char const* filename; struct file* file; int /*<<< orphan*/  argc; scalar_t__ buf; } ;
struct file {TYPE_1__* f_op; } ;
struct elfhdr {scalar_t__ e_type; scalar_t__ e_machine; int /*<<< orphan*/  e_ident; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmap; } ;

/* Variables and functions */
 int BINPRM_FLAGS_PATH_INACCESSIBLE ; 
 int /*<<< orphan*/  ELFMAG ; 
 char* EM86_INTERP ; 
 char* EM86_I_NAME ; 
 scalar_t__ EM_386 ; 
 scalar_t__ EM_486 ; 
 int ENOENT ; 
 int ENOEXEC ; 
 scalar_t__ ET_DYN ; 
 scalar_t__ ET_EXEC ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  SELFMAG ; 
 int /*<<< orphan*/  allow_write_access (struct file*) ; 
 int copy_strings_kernel (int,char const**,struct linux_binprm*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct file* open_exec (char*) ; 
 int prepare_binprm (struct linux_binprm*) ; 
 int /*<<< orphan*/  remove_arg_zero (struct linux_binprm*) ; 
 int search_binary_handler (struct linux_binprm*) ; 

__attribute__((used)) static int load_em86(struct linux_binprm *bprm)
{
	const char *i_name, *i_arg;
	char *interp;
	struct file * file;
	int retval;
	struct elfhdr	elf_ex;

	/* Make sure this is a Linux/Intel ELF executable... */
	elf_ex = *((struct elfhdr *)bprm->buf);

	if (memcmp(elf_ex.e_ident, ELFMAG, SELFMAG) != 0)
		return  -ENOEXEC;

	/* First of all, some simple consistency checks */
	if ((elf_ex.e_type != ET_EXEC && elf_ex.e_type != ET_DYN) ||
		(!((elf_ex.e_machine == EM_386) || (elf_ex.e_machine == EM_486))) ||
		!bprm->file->f_op->mmap) {
			return -ENOEXEC;
	}

	/* Need to be able to load the file after exec */
	if (bprm->interp_flags & BINPRM_FLAGS_PATH_INACCESSIBLE)
		return -ENOENT;

	allow_write_access(bprm->file);
	fput(bprm->file);
	bprm->file = NULL;

	/* Unlike in the script case, we don't have to do any hairy
	 * parsing to find our interpreter... it's hardcoded!
	 */
	interp = EM86_INTERP;
	i_name = EM86_I_NAME;
	i_arg = NULL;		/* We reserve the right to add an arg later */

	/*
	 * Splice in (1) the interpreter's name for argv[0]
	 *           (2) (optional) argument to interpreter
	 *           (3) filename of emulated file (replace argv[0])
	 *
	 * This is done in reverse order, because of how the
	 * user environment and arguments are stored.
	 */
	remove_arg_zero(bprm);
	retval = copy_strings_kernel(1, &bprm->filename, bprm);
	if (retval < 0) return retval; 
	bprm->argc++;
	if (i_arg) {
		retval = copy_strings_kernel(1, &i_arg, bprm);
		if (retval < 0) return retval; 
		bprm->argc++;
	}
	retval = copy_strings_kernel(1, &i_name, bprm);
	if (retval < 0)	return retval;
	bprm->argc++;

	/*
	 * OK, now restart the process with the interpreter's inode.
	 * Note that we use open_exec() as the name is now in kernel
	 * space, and we don't need to copy it.
	 */
	file = open_exec(interp);
	if (IS_ERR(file))
		return PTR_ERR(file);

	bprm->file = file;

	retval = prepare_binprm(bprm);
	if (retval < 0)
		return retval;

	return search_binary_handler(bprm);
}