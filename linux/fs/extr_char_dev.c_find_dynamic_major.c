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
struct char_device_struct {int major; struct char_device_struct* next; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct char_device_struct**) ; 
 int CHRDEV_MAJOR_DYN_END ; 
 int CHRDEV_MAJOR_DYN_EXT_END ; 
 int CHRDEV_MAJOR_DYN_EXT_START ; 
 int EBUSY ; 
 struct char_device_struct** chrdevs ; 
 size_t major_to_index (int) ; 

__attribute__((used)) static int find_dynamic_major(void)
{
	int i;
	struct char_device_struct *cd;

	for (i = ARRAY_SIZE(chrdevs)-1; i >= CHRDEV_MAJOR_DYN_END; i--) {
		if (chrdevs[i] == NULL)
			return i;
	}

	for (i = CHRDEV_MAJOR_DYN_EXT_START;
	     i >= CHRDEV_MAJOR_DYN_EXT_END; i--) {
		for (cd = chrdevs[major_to_index(i)]; cd; cd = cd->next)
			if (cd->major == i)
				break;

		if (cd == NULL)
			return i;
	}

	return -EBUSY;
}