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
 int /*<<< orphan*/  xa_empty (struct xarray*) ; 
 int /*<<< orphan*/  xa_erase (struct xarray*,int /*<<< orphan*/ ) ; 
 scalar_t__ xa_reserve (struct xarray*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xa_store (struct xarray*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_align_2(struct xarray *xa, char *name)
{
	int i;

	XA_BUG_ON(xa, !xa_empty(xa));

	for (i = 0; i < 8; i++) {
		XA_BUG_ON(xa, xa_store(xa, 0, name + i, GFP_KERNEL) != NULL);
		xa_erase(xa, 0);
	}

	for (i = 0; i < 8; i++) {
		XA_BUG_ON(xa, xa_reserve(xa, 0, GFP_KERNEL) != 0);
		XA_BUG_ON(xa, xa_store(xa, 0, name + i, 0) != NULL);
		xa_erase(xa, 0);
	}

	XA_BUG_ON(xa, !xa_empty(xa));
}