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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {unsigned int wMapLen; int /*<<< orphan*/  lpszPath; TYPE_1__* Map; } ;
struct TYPE_5__ {scalar_t__ lMap; int /*<<< orphan*/  offset; } ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HLPFILE_PAGE ;
typedef  TYPE_2__ HLPFILE ;

/* Variables and functions */
 int /*<<< orphan*/ * HLPFILE_PageByOffset (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WINE_ERR (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINE_TRACE (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  debugstr_a (int /*<<< orphan*/ ) ; 

HLPFILE_PAGE *HLPFILE_PageByMap(HLPFILE* hlpfile, LONG lMap, ULONG* relative)
{
    unsigned int i;

    if (!hlpfile) return 0;

    WINE_TRACE("<%s>[%x]\n", debugstr_a(hlpfile->lpszPath), lMap);

    for (i = 0; i < hlpfile->wMapLen; i++)
    {
        if (hlpfile->Map[i].lMap == lMap)
            return HLPFILE_PageByOffset(hlpfile, hlpfile->Map[i].offset, relative);
    }

    WINE_ERR("Page of Map %x not found in file %s\n", lMap, debugstr_a(hlpfile->lpszPath));
    return NULL;
}