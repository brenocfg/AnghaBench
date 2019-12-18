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
typedef  scalar_t__ xfs_agblock_t ;

/* Variables and functions */

__attribute__((used)) static int
xchk_agblock_cmp(
	const void		*pa,
	const void		*pb)
{
	const xfs_agblock_t	*a = pa;
	const xfs_agblock_t	*b = pb;

	return (int)*a - (int)*b;
}