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
struct the_nilfs {unsigned long ns_pseg_offset; int /*<<< orphan*/  ns_segctor_sem; } ;
struct nilfs_segctor_attr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
nilfs_segctor_next_pseg_offset_show(struct nilfs_segctor_attr *attr,
					struct the_nilfs *nilfs,
					char *buf)
{
	unsigned long pseg_offset;

	down_read(&nilfs->ns_segctor_sem);
	pseg_offset = nilfs->ns_pseg_offset;
	up_read(&nilfs->ns_segctor_sem);

	return snprintf(buf, PAGE_SIZE, "%lu\n", pseg_offset);
}