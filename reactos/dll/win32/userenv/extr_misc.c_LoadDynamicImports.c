#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * foo; } ;
struct TYPE_9__ {scalar_t__ hModule; TYPE_1__ fn; } ;
struct TYPE_8__ {int /*<<< orphan*/ ** Functions; int /*<<< orphan*/  Library; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_2__* PDYN_MODULE ;
typedef  TYPE_3__* PDYN_FUNCS ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  scalar_t__ HMODULE ;
typedef  int /*<<< orphan*/  DYN_FUNCS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/ * GetProcAddress (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ LoadLibraryW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_3__*,int) ; 

BOOL
LoadDynamicImports(PDYN_MODULE Module,
                   PDYN_FUNCS DynFuncs)
{
    LPSTR *fname;
    PVOID *fn;

    ZeroMemory(DynFuncs, sizeof(DYN_FUNCS));

    DynFuncs->hModule = LoadLibraryW(Module->Library);
    if (!DynFuncs->hModule)
    {
        return FALSE;
    }

    fn = &DynFuncs->fn.foo;

    /* load the imports */
    for (fname = Module->Functions; *fname != NULL; fname++)
    {
        *fn = GetProcAddress(DynFuncs->hModule, *fname);
        if (*fn == NULL)
        {
            FreeLibrary(DynFuncs->hModule);
            DynFuncs->hModule = (HMODULE)0;

            return FALSE;
        }

        fn++;
    }

    return TRUE;
}