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
 int /*<<< orphan*/  bfree (char*) ; 
 char* bmalloc (int) ; 
 int /*<<< orphan*/  os_get_abs_path (char const*,char*,int) ; 

char *os_get_abs_path_ptr(const char *path)
{
	char *ptr = bmalloc(512);

	if (!os_get_abs_path(path, ptr, 512)) {
		bfree(ptr);
		ptr = NULL;
	}

	return ptr;
}