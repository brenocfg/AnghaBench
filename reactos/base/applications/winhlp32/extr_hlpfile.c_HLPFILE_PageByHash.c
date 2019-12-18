#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_5__ {int version; size_t wTOMapLen; int /*<<< orphan*/  lpszPath; int /*<<< orphan*/  Context; int /*<<< orphan*/ * TOMap; } ;
typedef  size_t LONG ;
typedef  int /*<<< orphan*/  HLPFILE_PAGE ;
typedef  TYPE_1__ HLPFILE ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  GET_UINT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * HLPFILE_BPTreeSearch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HLPFILE_Contents (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HLPFILE_PageByOffset (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LongToPtr (size_t) ; 
 int /*<<< orphan*/  WINE_ERR (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINE_TRACE (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  comp_PageByHash ; 
 int /*<<< orphan*/  debugstr_a (int /*<<< orphan*/ ) ; 

HLPFILE_PAGE *HLPFILE_PageByHash(HLPFILE* hlpfile, LONG lHash, ULONG* relative)
{
    BYTE *ptr;

    if (!hlpfile) return NULL;
    if (!lHash) return HLPFILE_Contents(hlpfile, relative);

    WINE_TRACE("<%s>[%x]\n", debugstr_a(hlpfile->lpszPath), lHash);

    /* For win 3.0 files hash values are really page numbers */
    if (hlpfile->version <= 16)
    {
        if (lHash >= hlpfile->wTOMapLen) return NULL;
        return HLPFILE_PageByOffset(hlpfile, hlpfile->TOMap[lHash], relative);
    }

    ptr = HLPFILE_BPTreeSearch(hlpfile->Context, LongToPtr(lHash), comp_PageByHash);
    if (!ptr)
    {
        WINE_ERR("Page of hash %x not found in file %s\n", lHash, debugstr_a(hlpfile->lpszPath));
        return NULL;
    }

    return HLPFILE_PageByOffset(hlpfile, GET_UINT(ptr, 4), relative);
}