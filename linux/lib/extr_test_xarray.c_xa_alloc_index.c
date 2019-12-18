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
typedef  unsigned long u32 ;
struct xarray {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  XA_BUG_ON (struct xarray*,int) ; 
 scalar_t__ xa_alloc (struct xarray*,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_limit_32b ; 
 int /*<<< orphan*/  xa_mk_index (unsigned long) ; 

__attribute__((used)) static void xa_alloc_index(struct xarray *xa, unsigned long index, gfp_t gfp)
{
	u32 id;

	XA_BUG_ON(xa, xa_alloc(xa, &id, xa_mk_index(index), xa_limit_32b,
				gfp) != 0);
	XA_BUG_ON(xa, id != index);
}