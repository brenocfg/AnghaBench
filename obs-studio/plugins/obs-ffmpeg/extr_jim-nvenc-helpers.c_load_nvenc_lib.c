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

/* Variables and functions */
 int /*<<< orphan*/  nvenc_lib ; 
 int /*<<< orphan*/  os_dlopen (char*) ; 

bool load_nvenc_lib(void)
{
	if (sizeof(void *) == 8) {
		nvenc_lib = os_dlopen("nvEncodeAPI64.dll");
	} else {
		nvenc_lib = os_dlopen("nvEncodeAPI.dll");
	}

	return !!nvenc_lib;
}