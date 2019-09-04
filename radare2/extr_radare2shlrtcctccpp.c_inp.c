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
struct TYPE_2__ {scalar_t__* buf_ptr; } ;

/* Variables and functions */
 scalar_t__ CH_EOB ; 
 scalar_t__ ch ; 
 TYPE_1__* file ; 
 scalar_t__ handle_eob () ; 

void inp(void)
{
	ch = *(++(file->buf_ptr));
	/* end of buffer/file handling */
	if (ch == CH_EOB) {
		ch = handle_eob ();
	}
}