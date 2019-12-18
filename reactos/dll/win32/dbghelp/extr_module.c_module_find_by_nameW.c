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
struct process {struct module* lmodules; } ;
struct TYPE_2__ {int /*<<< orphan*/  ModuleName; } ;
struct module {TYPE_1__ module; struct module* next; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_NAME ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

struct module* module_find_by_nameW(const struct process* pcs, const WCHAR* name)
{
    struct module*      module;

    for (module = pcs->lmodules; module; module = module->next)
    {
        if (!strcmpiW(name, module->module.ModuleName)) return module;
    }
    SetLastError(ERROR_INVALID_NAME);
    return NULL;
}