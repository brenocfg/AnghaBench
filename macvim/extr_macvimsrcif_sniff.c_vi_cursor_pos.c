#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int linenr_T ;
struct TYPE_6__ {scalar_t__ b_p_tx; } ;
struct TYPE_4__ {int lnum; long col; } ;
struct TYPE_5__ {TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int STRLEN (int /*<<< orphan*/ ) ; 
 TYPE_3__* curbuf ; 
 TYPE_2__* curwin ; 
 int /*<<< orphan*/  ml_get (int) ; 

__attribute__((used)) static long
vi_cursor_pos()
{
    linenr_T	lnum;
    long	char_count=1;  /* sniff starts with pos 1 */
    int		line_size;
    int		eol_size;

    if (curbuf->b_p_tx)
	eol_size = 2;
    else
	eol_size = 1;
    for (lnum = 1; lnum < curwin->w_cursor.lnum; ++lnum)
    {
	line_size = STRLEN(ml_get(lnum)) + eol_size;
	char_count += line_size;
    }
    return char_count + curwin->w_cursor.col;
}