#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int index; TYPE_2__* set; } ;
struct TYPE_9__ {TYPE_3__ back; } ;
typedef  TYPE_4__ WINHELP_WINDOW ;
struct TYPE_7__ {TYPE_1__* page; } ;
struct TYPE_6__ {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  HLPFILE_FreeHlpFile (int /*<<< orphan*/ ) ; 

void WINHELP_DeleteBackSet(WINHELP_WINDOW* win)
{
    unsigned int i;

    for (i = 0; i < win->back.index; i++)
    {
        HLPFILE_FreeHlpFile(win->back.set[i].page->file);
        win->back.set[i].page = NULL;
    }
    win->back.index = 0;
}