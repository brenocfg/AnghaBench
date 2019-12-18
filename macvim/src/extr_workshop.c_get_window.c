#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * w_buffer; } ;
typedef  TYPE_1__ win_T ;
typedef  int /*<<< orphan*/  buf_T ;

/* Variables and functions */
 TYPE_1__* W_NEXT (TYPE_1__*) ; 
 TYPE_1__* firstwin ; 

__attribute__((used)) static win_T *
get_window(
	buf_T	*buf)		/* buffer to find window for */
{
    win_T	*wp = NULL;	/* window filename is in */

    for (wp = firstwin; wp != NULL; wp = W_NEXT(wp))
	if (buf == wp->w_buffer)
	    break;
    return wp;
}