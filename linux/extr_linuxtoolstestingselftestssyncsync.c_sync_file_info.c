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
typedef  scalar_t__ uint64_t ;
struct sync_file_info {int num_fences; scalar_t__ sync_fence_info; scalar_t__ flags; } ;
struct sync_fence_info {int num_fences; scalar_t__ sync_fence_info; scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_IOC_FILE_INFO ; 
 struct sync_file_info* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct sync_file_info*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct sync_file_info*) ; 

__attribute__((used)) static struct sync_file_info *sync_file_info(int fd)
{
	struct sync_file_info *info;
	struct sync_fence_info *fence_info;
	int err, num_fences;

	info = calloc(1, sizeof(*info));
	if (info == NULL)
		return NULL;

	err = ioctl(fd, SYNC_IOC_FILE_INFO, info);
	if (err < 0) {
		free(info);
		return NULL;
	}

	num_fences = info->num_fences;

	if (num_fences) {
		info->flags = 0;
		info->num_fences = num_fences;

		fence_info = calloc(num_fences, sizeof(*fence_info));
		if (!fence_info) {
			free(info);
			return NULL;
		}

		info->sync_fence_info = (uint64_t)fence_info;

		err = ioctl(fd, SYNC_IOC_FILE_INFO, info);
		if (err < 0) {
			free(fence_info);
			free(info);
			return NULL;
		}
	}

	return info;
}