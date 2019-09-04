#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int file_buffer_size; char* file_buffer; } ;
typedef  TYPE_1__ HLPFILE ;
typedef  int /*<<< orphan*/  HFILE ;
typedef  char BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GET_UINT (char*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINE_WARN (char*) ; 
 int _hread (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static BOOL HLPFILE_ReadFileToBuffer(HLPFILE* hlpfile, HFILE hFile)
{
    BYTE  header[16], dummy[1];

    if (_hread(hFile, header, 16) != 16) {WINE_WARN("header\n"); return FALSE;};

    /* sanity checks */
    if (GET_UINT(header, 0) != 0x00035F3F)
    {WINE_WARN("wrong header\n"); return FALSE;};

    hlpfile->file_buffer_size = GET_UINT(header, 12);
    hlpfile->file_buffer = HeapAlloc(GetProcessHeap(), 0, hlpfile->file_buffer_size + 1);
    if (!hlpfile->file_buffer) return FALSE;

    memcpy(hlpfile->file_buffer, header, 16);
    if (_hread(hFile, hlpfile->file_buffer + 16, hlpfile->file_buffer_size - 16) !=hlpfile->file_buffer_size - 16)
    {WINE_WARN("filesize1\n"); return FALSE;};

    if (_hread(hFile, dummy, 1) != 0) WINE_WARN("filesize2\n");

    hlpfile->file_buffer[hlpfile->file_buffer_size] = '\0'; /* FIXME: was '0', sounds backwards to me */

    return TRUE;
}