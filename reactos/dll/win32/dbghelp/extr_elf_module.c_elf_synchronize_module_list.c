#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct process {struct module* lmodules; } ;
struct module {scalar_t__ type; struct module* next; TYPE_3__** format_info; int /*<<< orphan*/  is_virtual; } ;
struct elf_module_info {int /*<<< orphan*/  elf_loader; scalar_t__ elf_mark; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct elf_load {int /*<<< orphan*/ * name; int /*<<< orphan*/  ret; TYPE_1__ elf_info; struct process* pcs; } ;
struct TYPE_5__ {struct elf_module_info* elf_info; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t DFI_ELF ; 
 scalar_t__ DMT_ELF ; 
 int /*<<< orphan*/  ELF_INFO_MODULE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  elf_enum_modules_internal (struct process*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct elf_load*) ; 
 int /*<<< orphan*/  elf_load_cb ; 
 int /*<<< orphan*/  module_remove (struct process*,struct module*) ; 

BOOL	elf_synchronize_module_list(struct process* pcs)
{
    struct module*      module;
    struct elf_load     el;

    for (module = pcs->lmodules; module; module = module->next)
    {
        if (module->type == DMT_ELF && !module->is_virtual)
            module->format_info[DFI_ELF]->u.elf_info->elf_mark = 0;
    }

    el.pcs = pcs;
    el.elf_info.flags = ELF_INFO_MODULE;
    el.ret = FALSE;
    el.name = NULL; /* fetch all modules */

    if (!elf_enum_modules_internal(pcs, NULL, elf_load_cb, &el))
        return FALSE;

    module = pcs->lmodules;
    while (module)
    {
        if (module->type == DMT_ELF && !module->is_virtual)
        {
            struct elf_module_info* elf_info = module->format_info[DFI_ELF]->u.elf_info;

            if (!elf_info->elf_mark && !elf_info->elf_loader)
            {
                module_remove(pcs, module);
                /* restart all over */
                module = pcs->lmodules;
                continue;
            }
        }
        module = module->next;
    }
    return TRUE;
}