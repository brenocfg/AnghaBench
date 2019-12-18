#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int w_jumplistlen; int w_jumplistidx; TYPE_3__* w_jumplist; } ;
struct TYPE_5__ {scalar_t__ lnum; } ;
struct TYPE_6__ {scalar_t__ fnum; TYPE_1__ mark; } ;
struct TYPE_7__ {int /*<<< orphan*/  fname; TYPE_2__ fmark; } ;

/* Variables and functions */
 TYPE_4__* curwin ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cleanup_jumplist()
{
    int	    i;
    int	    from, to;

    to = 0;
    for (from = 0; from < curwin->w_jumplistlen; ++from)
    {
	if (curwin->w_jumplistidx == from)
	    curwin->w_jumplistidx = to;
	for (i = from + 1; i < curwin->w_jumplistlen; ++i)
	    if (curwin->w_jumplist[i].fmark.fnum
					== curwin->w_jumplist[from].fmark.fnum
		    && curwin->w_jumplist[from].fmark.fnum != 0
		    && curwin->w_jumplist[i].fmark.mark.lnum
				  == curwin->w_jumplist[from].fmark.mark.lnum)
		break;
	if (i >= curwin->w_jumplistlen)	    /* no duplicate */
	    curwin->w_jumplist[to++] = curwin->w_jumplist[from];
	else
	    vim_free(curwin->w_jumplist[from].fname);
    }
    if (curwin->w_jumplistidx == curwin->w_jumplistlen)
	curwin->w_jumplistidx = to;
    curwin->w_jumplistlen = to;
}