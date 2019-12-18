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
struct sync_file_info {int num_fences; } ;

/* Variables and functions */
 struct sync_file_info* sync_file_info (int) ; 
 int /*<<< orphan*/  sync_file_info_free (struct sync_file_info*) ; 

int sync_fence_size(int fd)
{
	int count;
	struct sync_file_info *info = sync_file_info(fd);

	if (!info)
		return 0;

	count = info->num_fences;

	sync_file_info_free(info);

	return count;
}