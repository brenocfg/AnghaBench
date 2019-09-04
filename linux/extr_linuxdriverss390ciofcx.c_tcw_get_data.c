#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tcw {scalar_t__ output; scalar_t__ w; scalar_t__ input; scalar_t__ r; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */

void *tcw_get_data(struct tcw *tcw)
{
	if (tcw->r)
		return (void *) ((addr_t) tcw->input);
	if (tcw->w)
		return (void *) ((addr_t) tcw->output);
	return NULL;
}