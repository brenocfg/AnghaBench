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
typedef  scalar_t__ u16 ;
struct aty128fb_par {scalar_t__ fifo_slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_wait_for_fifo (int,struct aty128fb_par*) ; 

__attribute__((used)) static void wait_for_fifo(u16 entries, struct aty128fb_par *par)
{
	if (par->fifo_slots < entries)
		do_wait_for_fifo(64, par);
	par->fifo_slots -= entries;
}