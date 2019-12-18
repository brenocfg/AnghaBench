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
struct TYPE_5__ {int /*<<< orphan*/ * b_next; } ;
struct TYPE_6__ {TYPE_1__ bh_first; } ;

/* Variables and functions */
 int /*<<< orphan*/  block_redo ; 
 int /*<<< orphan*/  free_buff (TYPE_2__*) ; 
 TYPE_2__ old_redobuff ; 
 TYPE_2__ redobuff ; 

void
ResetRedobuff()
{
    if (!block_redo)
    {
	free_buff(&old_redobuff);
	old_redobuff = redobuff;
	redobuff.bh_first.b_next = NULL;
    }
}