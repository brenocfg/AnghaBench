#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pdb_lookup {int /*<<< orphan*/  filename; } ;
struct pdb_file_info {int dummy; } ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileMappingW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_MAP_READ ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 char* MapViewOfFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  UnmapViewOfFile (char*) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdb_free_file (struct pdb_file_info*) ; 
 int /*<<< orphan*/  pdb_init (struct pdb_lookup const*,struct pdb_file_info*,char*,unsigned int*) ; 

BOOL pdb_fetch_file_info(const struct pdb_lookup* pdb_lookup, unsigned* matched)
{
    HANDLE              hFile, hMap = NULL;
    char*               image = NULL;
    BOOL                ret;
    struct pdb_file_info pdb_file;

    if ((hFile = CreateFileA(pdb_lookup->filename, GENERIC_READ, FILE_SHARE_READ, NULL,
                             OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE ||
        ((hMap = CreateFileMappingW(hFile, NULL, PAGE_READONLY, 0, 0, NULL)) == NULL) ||
        ((image = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0)) == NULL))
    {
        WARN("Unable to open .PDB file: %s\n", pdb_lookup->filename);
        ret = FALSE;
    }
    else
    {
        ret = pdb_init(pdb_lookup, &pdb_file, image, matched);
        pdb_free_file(&pdb_file);
    }

    if (image) UnmapViewOfFile(image);
    if (hMap) CloseHandle(hMap);
    if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

    return ret;
}