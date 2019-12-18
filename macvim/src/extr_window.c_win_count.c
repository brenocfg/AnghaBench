#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__* w_next; } ;
typedef  TYPE_1__ win_T ;

/* Variables and functions */
 TYPE_1__* firstwin ; 

int
win_count()
{
    win_T	*wp;
    int		count = 0;

    for (wp = firstwin; wp != NULL; wp = wp->w_next)
	++count;
    return count;
}