#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct module {int dummy; } ;
struct TYPE_3__ {size_t pcpu; size_t mod; } ;
struct load_info {TYPE_1__ index; TYPE_2__* sechdrs; int /*<<< orphan*/  mod; int /*<<< orphan*/  secstrings; int /*<<< orphan*/  hdr; } ;
struct TYPE_4__ {unsigned long sh_flags; scalar_t__ sh_addr; } ;

/* Variables and functions */
 struct module* ERR_PTR (int) ; 
 scalar_t__ SHF_ALLOC ; 
 unsigned long SHF_RO_AFTER_INIT ; 
 int check_modinfo (int /*<<< orphan*/ ,struct load_info*,int) ; 
 unsigned int find_sec (struct load_info*,char*) ; 
 int /*<<< orphan*/  kmemleak_load_module (struct module*,struct load_info*) ; 
 int /*<<< orphan*/  layout_sections (int /*<<< orphan*/ ,struct load_info*) ; 
 int /*<<< orphan*/  layout_symtab (int /*<<< orphan*/ ,struct load_info*) ; 
 int module_frob_arch_sections (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int move_module (int /*<<< orphan*/ ,struct load_info*) ; 

__attribute__((used)) static struct module *layout_and_allocate(struct load_info *info, int flags)
{
	struct module *mod;
	unsigned int ndx;
	int err;

	err = check_modinfo(info->mod, info, flags);
	if (err)
		return ERR_PTR(err);

	/* Allow arches to frob section contents and sizes.  */
	err = module_frob_arch_sections(info->hdr, info->sechdrs,
					info->secstrings, info->mod);
	if (err < 0)
		return ERR_PTR(err);

	/* We will do a special allocation for per-cpu sections later. */
	info->sechdrs[info->index.pcpu].sh_flags &= ~(unsigned long)SHF_ALLOC;

	/*
	 * Mark ro_after_init section with SHF_RO_AFTER_INIT so that
	 * layout_sections() can put it in the right place.
	 * Note: ro_after_init sections also have SHF_{WRITE,ALLOC} set.
	 */
	ndx = find_sec(info, ".data..ro_after_init");
	if (ndx)
		info->sechdrs[ndx].sh_flags |= SHF_RO_AFTER_INIT;
	/*
	 * Mark the __jump_table section as ro_after_init as well: these data
	 * structures are never modified, with the exception of entries that
	 * refer to code in the __init section, which are annotated as such
	 * at module load time.
	 */
	ndx = find_sec(info, "__jump_table");
	if (ndx)
		info->sechdrs[ndx].sh_flags |= SHF_RO_AFTER_INIT;

	/* Determine total sizes, and put offsets in sh_entsize.  For now
	   this is done generically; there doesn't appear to be any
	   special cases for the architectures. */
	layout_sections(info->mod, info);
	layout_symtab(info->mod, info);

	/* Allocate and move to the final place */
	err = move_module(info->mod, info);
	if (err)
		return ERR_PTR(err);

	/* Module has been copied to its final place now: return it. */
	mod = (void *)info->sechdrs[info->index.mod].sh_addr;
	kmemleak_load_module(mod, info);
	return mod;
}