#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* w_height; } ;
struct TYPE_3__ {void* fr_height; } ;

/* Variables and functions */
 void* ROWS_AVAIL ; 
 TYPE_2__* firstwin ; 
 TYPE_1__* topframe ; 

void
win_init_size()
{
    firstwin->w_height = ROWS_AVAIL;
    topframe->fr_height = ROWS_AVAIL;
#ifdef FEAT_VERTSPLIT
    firstwin->w_width = Columns;
    topframe->fr_width = Columns;
#endif
}