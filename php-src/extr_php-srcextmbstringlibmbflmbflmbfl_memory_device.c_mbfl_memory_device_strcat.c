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
typedef  int /*<<< orphan*/  mbfl_memory_device ;

/* Variables and functions */
 int mbfl_memory_device_strncat (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int
mbfl_memory_device_strcat(mbfl_memory_device *device, const char *psrc)
{
	return mbfl_memory_device_strncat(device, psrc, strlen(psrc));
}