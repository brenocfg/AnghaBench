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
struct xfs_defer_op_type {size_t type; } ;

/* Variables and functions */
 struct xfs_defer_op_type const** defer_op_types ; 

void
xfs_defer_init_op_type(
	const struct xfs_defer_op_type	*type)
{
	defer_op_types[type->type] = type;
}