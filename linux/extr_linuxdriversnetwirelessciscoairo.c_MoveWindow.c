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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ window; scalar_t__ rx; } ;
typedef  TYPE_1__ miccntx ;

/* Variables and functions */

__attribute__((used)) static void MoveWindow(miccntx *context, u32 micSeq)
{
	u32 shift;

	//Move window if seq greater than the middle of the window
	if (micSeq > context->window) {
		shift = (micSeq - context->window) >> 1;
    
		    //Shift out old
		if (shift < 32)
			context->rx >>= shift;
		else
			context->rx = 0;

		context->window = micSeq;      //Move window
	}
}