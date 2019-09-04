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
typedef  int ULONG ;
struct TYPE_6__ {int /*<<< orphan*/  lpszPath; TYPE_1__* first_page; } ;
struct TYPE_5__ {int offset; struct TYPE_5__* next; } ;
typedef  int LONG ;
typedef  TYPE_1__ HLPFILE_PAGE ;
typedef  TYPE_2__ HLPFILE ;

/* Variables and functions */
 int /*<<< orphan*/  WINE_ERR (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINE_TRACE (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugstr_a (int /*<<< orphan*/ ) ; 

HLPFILE_PAGE *HLPFILE_PageByOffset(HLPFILE* hlpfile, LONG offset, ULONG* relative)
{
    HLPFILE_PAGE*       page;
    HLPFILE_PAGE*       found;

    if (!hlpfile) return 0;

    WINE_TRACE("<%s>[%x]\n", debugstr_a(hlpfile->lpszPath), offset);

    if (offset == 0xFFFFFFFF) return NULL;
    page = NULL;

    for (found = NULL, page = hlpfile->first_page; page; page = page->next)
    {
        if (page->offset <= offset && (!found || found->offset < page->offset))
        {
            *relative = offset - page->offset;
            found = page;
        }
    }
    if (!found)
        WINE_ERR("Page of offset %u not found in file %s\n",
                 offset, debugstr_a(hlpfile->lpszPath));
    return found;
}