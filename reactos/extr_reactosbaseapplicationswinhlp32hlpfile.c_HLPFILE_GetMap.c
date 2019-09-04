#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* offset; void* lMap; } ;
struct TYPE_5__ {unsigned int wMapLen; TYPE_2__* Map; } ;
typedef  int /*<<< orphan*/  HLPFILE_MAP ;
typedef  TYPE_1__ HLPFILE ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* GET_UINT (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int GET_USHORT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HLPFILE_FindSubFile (TYPE_1__*,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WINE_WARN (char*) ; 

__attribute__((used)) static BOOL HLPFILE_GetMap(HLPFILE *hlpfile)
{
    BYTE                *cbuf, *cend;
    unsigned            entries, i;

    if (!HLPFILE_FindSubFile(hlpfile, "|CTXOMAP",  &cbuf, &cend))
    {WINE_WARN("no map section\n"); return FALSE;}

    entries = GET_USHORT(cbuf, 9);
    hlpfile->Map = HeapAlloc(GetProcessHeap(), 0, entries * sizeof(HLPFILE_MAP));
    if (!hlpfile->Map) return FALSE;
    hlpfile->wMapLen = entries;
    for (i = 0; i < entries; i++)
    {
        hlpfile->Map[i].lMap = GET_UINT(cbuf+11,i*8);
        hlpfile->Map[i].offset = GET_UINT(cbuf+11,i*8+4);
    }
    return TRUE;
}