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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 int ENOSYS ; 

int do_migrate_pages(struct mm_struct *mm, const nodemask_t *from,
		     const nodemask_t *to, int flags)
{
	return -ENOSYS;
}