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
struct process {int dummy; } ;
struct pdb_lookup {int kind; int /*<<< orphan*/  filename; int /*<<< orphan*/  age; int /*<<< orphan*/  guid; int /*<<< orphan*/  timestamp; } ;
struct TYPE_2__ {int /*<<< orphan*/  PdbUnmatched; } ;
struct module {TYPE_1__ module; } ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileMappingW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
#define  PDB_DS 129 
#define  PDB_JG 128 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_find_symbol_file (struct process const*,struct module*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HANDLE map_pdb_file(const struct process* pcs,
                           const struct pdb_lookup* lookup,
                           struct module* module)
{
    HANDLE      hFile, hMap = NULL;
    char        dbg_file_path[MAX_PATH];
    BOOL        ret = FALSE;

    switch (lookup->kind)
    {
    case PDB_JG:
        ret = path_find_symbol_file(pcs, module, lookup->filename, NULL, lookup->timestamp,
                                    lookup->age, dbg_file_path, &module->module.PdbUnmatched);
        break;
    case PDB_DS:
        ret = path_find_symbol_file(pcs, module, lookup->filename, &lookup->guid, 0,
                                    lookup->age, dbg_file_path, &module->module.PdbUnmatched);
        break;
    }
    if (!ret)
    {
        WARN("\tCouldn't find %s\n", lookup->filename);
        return NULL;
    }
    if ((hFile = CreateFileA(dbg_file_path, GENERIC_READ, FILE_SHARE_READ, NULL,
                             OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
    {
        hMap = CreateFileMappingW(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
        CloseHandle(hFile);
    }
    return hMap;
}