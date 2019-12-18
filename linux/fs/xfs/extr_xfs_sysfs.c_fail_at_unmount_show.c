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
struct xfs_mount {int m_fail_unmount; } ;
struct kobject {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct xfs_mount* err_to_mp (struct kobject*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t
fail_at_unmount_show(
	struct kobject	*kobject,
	char		*buf)
{
	struct xfs_mount	*mp = err_to_mp(kobject);

	return snprintf(buf, PAGE_SIZE, "%d\n", mp->m_fail_unmount);
}