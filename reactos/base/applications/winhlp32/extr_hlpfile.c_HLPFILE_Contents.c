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
typedef  scalar_t__ ULONG ;
struct TYPE_4__ {int /*<<< orphan*/ * first_page; int /*<<< orphan*/  contents_start; } ;
typedef  int /*<<< orphan*/  HLPFILE_PAGE ;
typedef  TYPE_1__ HLPFILE ;

/* Variables and functions */
 int /*<<< orphan*/ * HLPFILE_PageByOffset (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static HLPFILE_PAGE* HLPFILE_Contents(HLPFILE *hlpfile, ULONG* relative)
{
    HLPFILE_PAGE*       page = NULL;

    if (!hlpfile) return NULL;

    page = HLPFILE_PageByOffset(hlpfile, hlpfile->contents_start, relative);
    if (!page)
    {
        page = hlpfile->first_page;
        *relative = 0;
    }
    return page;
}