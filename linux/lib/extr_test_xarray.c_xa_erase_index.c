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
struct xarray {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XA_BUG_ON (struct xarray*,int) ; 
 scalar_t__ xa_erase (struct xarray*,unsigned long) ; 
 int /*<<< orphan*/ * xa_load (struct xarray*,unsigned long) ; 
 scalar_t__ xa_mk_index (unsigned long) ; 

__attribute__((used)) static void xa_erase_index(struct xarray *xa, unsigned long index)
{
	XA_BUG_ON(xa, xa_erase(xa, index) != xa_mk_index(index));
	XA_BUG_ON(xa, xa_load(xa, index) != NULL);
}