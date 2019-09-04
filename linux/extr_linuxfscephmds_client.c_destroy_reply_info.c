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
struct ceph_mds_reply_info_parsed {int /*<<< orphan*/  dir_buf_size; scalar_t__ dir_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_reply_info(struct ceph_mds_reply_info_parsed *info)
{
	if (!info->dir_entries)
		return;
	free_pages((unsigned long)info->dir_entries, get_order(info->dir_buf_size));
}