#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vfio_group {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  group_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MINORMASK ; 
 int idr_alloc (int /*<<< orphan*/ *,struct vfio_group*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__ vfio ; 

__attribute__((used)) static int vfio_alloc_group_minor(struct vfio_group *group)
{
	return idr_alloc(&vfio.group_idr, group, 0, MINORMASK + 1, GFP_KERNEL);
}