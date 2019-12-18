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
struct TYPE_2__ {scalar_t__ BaseOfImage; scalar_t__ ImageSize; int /*<<< orphan*/  const* LoadedImageName; } ;
struct module {scalar_t__ type; TYPE_1__ module; struct module* next; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ PCWSTR ;
typedef  scalar_t__ DWORD64 ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ DMT_ELF ; 
 scalar_t__ DMT_MACHO ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  S_DotSoW ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 scalar_t__ get_filename (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (scalar_t__,int /*<<< orphan*/ ,int) ; 
 size_t strlenW (scalar_t__) ; 
 int /*<<< orphan*/  strncmpiW (scalar_t__,scalar_t__,size_t) ; 

__attribute__((used)) static BOOL module_is_container_loaded(const struct process* pcs,
                                       const WCHAR* ImageName, DWORD64 base)
{
    size_t              len;
    struct module*      module;
    PCWSTR              filename, modname;

    if (!base) return FALSE;
    filename = get_filename(ImageName, NULL);
    len = strlenW(filename);

    for (module = pcs->lmodules; module; module = module->next)
    {
        if ((module->type == DMT_ELF || module->type == DMT_MACHO) &&
            base >= module->module.BaseOfImage &&
            base < module->module.BaseOfImage + module->module.ImageSize)
        {
            modname = get_filename(module->module.LoadedImageName, NULL);
            if (!strncmpiW(modname, filename, len) &&
                !memcmp(modname + len, S_DotSoW, 3 * sizeof(WCHAR)))
            {
                return TRUE;
            }
        }
    }
    /* likely a native PE module */
    WARN("Couldn't find container for %s\n", debugstr_w(ImageName));
    return FALSE;
}