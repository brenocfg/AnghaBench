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
struct sw_sync_create_fence_data {unsigned int value; char* name; int fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  SW_SYNC_IOC_CREATE_FENCE ; 
 int ioctl (int,int /*<<< orphan*/ ,struct sw_sync_create_fence_data*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

int sw_sync_fence_create(int fd, const char *name, unsigned int value)
{
	struct sw_sync_create_fence_data data = {};
	int err;

	data.value = value;
	strncpy(data.name, name, sizeof(data.name) - 1);
	data.name[sizeof(data.name) - 1] = '\0';

	err = ioctl(fd, SW_SYNC_IOC_CREATE_FENCE, &data);
	if (err < 0)
		return err;

	return data.fence;
}