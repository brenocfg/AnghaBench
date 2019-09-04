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
struct list_head {int dummy; } ;

/* Variables and functions */
 int xfs_buf_delwri_submit_buffers (struct list_head*,int /*<<< orphan*/ *) ; 

int
xfs_buf_delwri_submit_nowait(
	struct list_head	*buffer_list)
{
	return xfs_buf_delwri_submit_buffers(buffer_list, NULL);
}