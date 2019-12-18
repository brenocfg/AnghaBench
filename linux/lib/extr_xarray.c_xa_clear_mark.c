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
typedef  int /*<<< orphan*/  xa_mark_t ;
struct xarray {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xa_clear_mark (struct xarray*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_lock (struct xarray*) ; 
 int /*<<< orphan*/  xa_unlock (struct xarray*) ; 

void xa_clear_mark(struct xarray *xa, unsigned long index, xa_mark_t mark)
{
	xa_lock(xa);
	__xa_clear_mark(xa, index, mark);
	xa_unlock(xa);
}