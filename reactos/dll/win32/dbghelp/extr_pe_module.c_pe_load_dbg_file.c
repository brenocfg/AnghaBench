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
struct process {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  DbgUnmatched; } ;
struct module {TYPE_1__ module; } ;
struct TYPE_4__ {int NumberOfSections; int ExportedNamesSize; int DebugDirectorySize; } ;
typedef  TYPE_2__ IMAGE_SEPARATE_DEBUG_HEADER ;
typedef  int /*<<< orphan*/  IMAGE_SECTION_HEADER ;
typedef  int /*<<< orphan*/  IMAGE_DEBUG_DIRECTORY ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileMappingW (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_MAP_READ ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * MapViewOfFile (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnmapViewOfFile (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 scalar_t__ path_find_symbol_file (struct process const*,struct module*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pe_load_debug_directory (struct process const*,struct module*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static BOOL pe_load_dbg_file(const struct process* pcs, struct module* module,
                             const char* dbg_name, DWORD timestamp)
{
    char                                tmp[MAX_PATH];
    HANDLE                              hFile = INVALID_HANDLE_VALUE, hMap = 0;
    const BYTE*                         dbg_mapping = NULL;
    BOOL                                ret = FALSE;

    TRACE("Processing DBG file %s\n", debugstr_a(dbg_name));

    if (path_find_symbol_file(pcs, module, dbg_name, NULL, timestamp, 0, tmp, &module->module.DbgUnmatched) &&
        (hFile = CreateFileA(tmp, GENERIC_READ, FILE_SHARE_READ, NULL,
                             OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE &&
        ((hMap = CreateFileMappingW(hFile, NULL, PAGE_READONLY, 0, 0, NULL)) != 0) &&
        ((dbg_mapping = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0)) != NULL))
    {
        const IMAGE_SEPARATE_DEBUG_HEADER*      hdr;
        const IMAGE_SECTION_HEADER*             sectp;
        const IMAGE_DEBUG_DIRECTORY*            dbg;

        hdr = (const IMAGE_SEPARATE_DEBUG_HEADER*)dbg_mapping;
        /* section headers come immediately after debug header */
        sectp = (const IMAGE_SECTION_HEADER*)(hdr + 1);
        /* and after that and the exported names comes the debug directory */
        dbg = (const IMAGE_DEBUG_DIRECTORY*)
            (dbg_mapping + sizeof(*hdr) +
             hdr->NumberOfSections * sizeof(IMAGE_SECTION_HEADER) +
             hdr->ExportedNamesSize);

        ret = pe_load_debug_directory(pcs, module, dbg_mapping, sectp,
                                      hdr->NumberOfSections, dbg,
                                      hdr->DebugDirectorySize / sizeof(*dbg));
    }
    else
        ERR("Couldn't find .DBG file %s (%s)\n", debugstr_a(dbg_name), debugstr_a(tmp));

    if (dbg_mapping) UnmapViewOfFile(dbg_mapping);
    if (hMap) CloseHandle(hMap);
    if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);
    return ret;
}