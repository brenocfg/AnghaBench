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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  XA_BUG_ON (struct xarray*,int) ; 
 scalar_t__ xa_insert (struct xarray*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_mk_index (unsigned long) ; 

__attribute__((used)) static void xa_insert_index(struct xarray *xa, unsigned long index)
{
	XA_BUG_ON(xa, xa_insert(xa, index, xa_mk_index(index),
				GFP_KERNEL) != 0);
}