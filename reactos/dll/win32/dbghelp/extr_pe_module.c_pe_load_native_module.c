#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct process {int /*<<< orphan*/  search_path; } ;
struct TYPE_12__ {scalar_t__ ImageBase; int /*<<< orphan*/  CheckSum; int /*<<< orphan*/  SizeOfImage; } ;
struct TYPE_10__ {int /*<<< orphan*/  TimeDateStamp; } ;
struct TYPE_13__ {TYPE_3__ OptionalHeader; TYPE_1__ FileHeader; } ;
struct TYPE_14__ {TYPE_4__ ntheader; } ;
struct TYPE_15__ {TYPE_5__ pe; } ;
struct TYPE_17__ {TYPE_6__ u; } ;
struct pe_module_info {TYPE_8__ fmap; } ;
struct TYPE_16__ {struct pe_module_info* pe_info; } ;
struct module_format {TYPE_7__ u; int /*<<< orphan*/ * loc_compute; int /*<<< orphan*/  remove; struct module* module; } ;
struct TYPE_11__ {int /*<<< orphan*/  SymType; } ;
struct module {scalar_t__ reloc_delta; TYPE_2__ module; struct module_format** format_info; } ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD64 ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 size_t DFI_PE ; 
 int /*<<< orphan*/  DMT_PE ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/ * FindExecutableImageExW (char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct module_format* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct module_format*) ; 
 int MAX_PATH ; 
 int SYMOPT_DEFERRED_LOADS ; 
 int /*<<< orphan*/  SymDeferred ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int dbghelp_options ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 struct module* module_new (struct process*,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pe_load_debug_info (struct process*,struct module*) ; 
 scalar_t__ pe_map_file (int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pe_module_remove ; 
 int /*<<< orphan*/  pe_unmap_file (TYPE_8__*) ; 
 int /*<<< orphan*/  strcpyW (char*,char const*) ; 

struct module* pe_load_native_module(struct process* pcs, const WCHAR* name,
                                     HANDLE hFile, DWORD64 base, DWORD size)
{
    struct module*              module = NULL;
    BOOL                        opened = FALSE;
    struct module_format*       modfmt;
    WCHAR                       loaded_name[MAX_PATH];

    loaded_name[0] = '\0';
    if (!hFile)
    {
        assert(name);

        if ((hFile = FindExecutableImageExW(name, pcs->search_path, loaded_name, NULL, NULL)) == NULL)
            return NULL;
        opened = TRUE;
    }
    else if (name) strcpyW(loaded_name, name);
    else if (dbghelp_options & SYMOPT_DEFERRED_LOADS)
        FIXME("Trouble ahead (no module name passed in deferred mode)\n");
    if (!(modfmt = HeapAlloc(GetProcessHeap(), 0, sizeof(struct module_format) + sizeof(struct pe_module_info))))
        return NULL;
    modfmt->u.pe_info = (struct pe_module_info*)(modfmt + 1);
    if (pe_map_file(hFile, &modfmt->u.pe_info->fmap, DMT_PE))
    {
        if (!base) base = modfmt->u.pe_info->fmap.u.pe.ntheader.OptionalHeader.ImageBase;
        if (!size) size = modfmt->u.pe_info->fmap.u.pe.ntheader.OptionalHeader.SizeOfImage;

        module = module_new(pcs, loaded_name, DMT_PE, FALSE, base, size,
                            modfmt->u.pe_info->fmap.u.pe.ntheader.FileHeader.TimeDateStamp,
                            modfmt->u.pe_info->fmap.u.pe.ntheader.OptionalHeader.CheckSum);
        if (module)
        {
            modfmt->module = module;
            modfmt->remove = pe_module_remove;
            modfmt->loc_compute = NULL;

            module->format_info[DFI_PE] = modfmt;
            if (dbghelp_options & SYMOPT_DEFERRED_LOADS)
                module->module.SymType = SymDeferred;
            else
                pe_load_debug_info(pcs, module);
            module->reloc_delta = base - modfmt->u.pe_info->fmap.u.pe.ntheader.OptionalHeader.ImageBase;
        }
        else
        {
            ERR("could not load the module '%s'\n", debugstr_w(loaded_name));
            pe_unmap_file(&modfmt->u.pe_info->fmap);
        }
    }
    if (!module) HeapFree(GetProcessHeap(), 0, modfmt);

    if (opened) CloseHandle(hFile);

    return module;
}