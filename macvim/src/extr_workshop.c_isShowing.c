#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int w_topline; int w_botline; } ;
typedef  int Boolean ;

/* Variables and functions */
 TYPE_1__* curwin ; 

__attribute__((used)) static Boolean
isShowing(
	int	 lnum)			/* tell if line number is showing */
{
    return lnum >= curwin->w_topline && lnum < curwin->w_botline;
}