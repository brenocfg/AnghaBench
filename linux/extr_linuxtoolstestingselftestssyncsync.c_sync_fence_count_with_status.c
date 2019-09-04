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
struct sync_file_info {unsigned int num_fences; scalar_t__ sync_fence_info; } ;
struct sync_fence_info {int status; } ;

/* Variables and functions */
 struct sync_file_info* sync_file_info (int) ; 
 int /*<<< orphan*/  sync_file_info_free (struct sync_file_info*) ; 

int sync_fence_count_with_status(int fd, int status)
{
	unsigned int i, count = 0;
	struct sync_fence_info *fence_info = NULL;
	struct sync_file_info *info = sync_file_info(fd);

	if (!info)
		return -1;

	fence_info = (struct sync_fence_info *)info->sync_fence_info;
	for (i = 0 ; i < info->num_fences ; i++) {
		if (fence_info[i].status == status)
			count++;
	}

	sync_file_info_free(info);

	return count;
}