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
typedef  int /*<<< orphan*/  NDBOX ;

/* Variables and functions */
 int VARSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cube_union_v0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

NDBOX *
g_cube_binary_union(NDBOX *r1, NDBOX *r2, int *sizep)
{
	NDBOX	   *retval;

	retval = cube_union_v0(r1, r2);
	*sizep = VARSIZE(retval);

	return retval;
}