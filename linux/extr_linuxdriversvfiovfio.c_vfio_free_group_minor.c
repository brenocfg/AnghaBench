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
struct TYPE_2__ {int /*<<< orphan*/  group_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 TYPE_1__ vfio ; 

__attribute__((used)) static void vfio_free_group_minor(int minor)
{
	idr_remove(&vfio.group_idr, minor);
}