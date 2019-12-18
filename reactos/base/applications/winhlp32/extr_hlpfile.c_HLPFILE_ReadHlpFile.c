#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* lpszPath; int wRefCount; int contents_start; struct TYPE_7__* prev; struct TYPE_7__* next; } ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  TYPE_1__ HLPFILE ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HLPFILE_DoReadHlpFile (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HLPFILE_FreeHlpFile (TYPE_1__*) ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* first_hlpfile ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

HLPFILE *HLPFILE_ReadHlpFile(LPCSTR lpszPath)
{
    HLPFILE*      hlpfile;

    for (hlpfile = first_hlpfile; hlpfile; hlpfile = hlpfile->next)
    {
        if (!strcmp(lpszPath, hlpfile->lpszPath))
        {
            hlpfile->wRefCount++;
            return hlpfile;
        }
    }

    hlpfile = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                        sizeof(HLPFILE) + strlen(lpszPath) + 1);
    if (!hlpfile) return 0;

    hlpfile->lpszPath           = (char*)hlpfile + sizeof(HLPFILE);
    hlpfile->contents_start     = 0xFFFFFFFF;
    hlpfile->next               = first_hlpfile;
    hlpfile->wRefCount          = 1;

    strcpy(hlpfile->lpszPath, lpszPath);

    first_hlpfile = hlpfile;
    if (hlpfile->next) hlpfile->next->prev = hlpfile;

    if (!HLPFILE_DoReadHlpFile(hlpfile, lpszPath))
    {
        HLPFILE_FreeHlpFile(hlpfile);
        hlpfile = 0;
    }

    return hlpfile;
}