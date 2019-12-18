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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  HRSRC ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/ * HGLOBAL ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FindResourceW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeResource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/ * LoadResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LockResource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REGINST ; 
 scalar_t__ SizeofResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_temp_ini_path (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL create_tmp_ini_file(HMODULE hm, WCHAR *ini_file)
{
    HRSRC hrsrc;
    HGLOBAL hmem = NULL;
    DWORD rsrc_size, bytes_written;
    VOID *rsrc_data;
    HANDLE hf = INVALID_HANDLE_VALUE;

    if(!get_temp_ini_path(ini_file)) {
        ERR("Can't get temp ini file path\n");
        goto error;
    }

    if(!(hrsrc = FindResourceW(hm, REGINST, REGINST))) {
        ERR("Can't find REGINST resource\n");
        goto error;
    }

    rsrc_size = SizeofResource(hm, hrsrc);
    hmem = LoadResource(hm, hrsrc);
    rsrc_data = LockResource(hmem);

    if(!rsrc_data || !rsrc_size) {
        ERR("Can't load REGINST resource\n");
        goto error;
    }       

    if((hf = CreateFileW(ini_file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                         FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE) {
        ERR("Unable to create temp ini file\n");
        goto error;
    }
    if(!WriteFile(hf, rsrc_data, rsrc_size, &bytes_written, NULL) || rsrc_size != bytes_written) {
        ERR("Write failed\n");
        goto error;
    }
    FreeResource(hmem);
    CloseHandle(hf);
    return TRUE;
error:
    if(hmem) FreeResource(hmem);
    if(hf != INVALID_HANDLE_VALUE) CloseHandle(hf);
    return FALSE;
}