#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* kwdata; void* kwbtree; } ;
typedef  TYPE_1__ HLPFILE ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HLPFILE_FindSubFile (TYPE_1__*,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINE_ERR (char*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static BOOL HLPFILE_GetKeywords(HLPFILE *hlpfile)
{
    BYTE                *cbuf, *cend;
    unsigned            clen;

    if (!HLPFILE_FindSubFile(hlpfile, "|KWBTREE", &cbuf, &cend)) return FALSE;
    clen = cend - cbuf;
    hlpfile->kwbtree = HeapAlloc(GetProcessHeap(), 0, clen);
    if (!hlpfile->kwbtree) return FALSE;
    memcpy(hlpfile->kwbtree, cbuf, clen);

    if (!HLPFILE_FindSubFile(hlpfile, "|KWDATA", &cbuf, &cend))
    {
        WINE_ERR("corrupted help file: kwbtree present but kwdata absent\n");
        HeapFree(GetProcessHeap(), 0, hlpfile->kwbtree);
        return FALSE;
    }
    clen = cend - cbuf;
    hlpfile->kwdata = HeapAlloc(GetProcessHeap(), 0, clen);
    if (!hlpfile->kwdata)
    {
        HeapFree(GetProcessHeap(), 0, hlpfile->kwdata);
        return FALSE;
    }
    memcpy(hlpfile->kwdata, cbuf, clen);

    return TRUE;
}