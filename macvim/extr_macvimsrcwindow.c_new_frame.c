#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* w_frame; } ;
typedef  TYPE_1__ win_T ;
struct TYPE_5__ {TYPE_1__* fr_win; int /*<<< orphan*/  fr_layout; } ;
typedef  TYPE_2__ frame_T ;

/* Variables and functions */
 int /*<<< orphan*/  FR_LEAF ; 
 scalar_t__ alloc_clear (unsigned int) ; 

__attribute__((used)) static void
new_frame(win_T *wp)
{
    frame_T *frp = (frame_T *)alloc_clear((unsigned)sizeof(frame_T));

    wp->w_frame = frp;
    if (frp != NULL)
    {
	frp->fr_layout = FR_LEAF;
	frp->fr_win = wp;
    }
}