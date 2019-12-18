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
struct xfs_iunlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (struct xfs_iunlink*) ; 

__attribute__((used)) static void
xfs_iunlink_free_item(
	void			*ptr,
	void			*arg)
{
	struct xfs_iunlink	*iu = ptr;
	bool			*freed_anything = arg;

	*freed_anything = true;
	kmem_free(iu);
}