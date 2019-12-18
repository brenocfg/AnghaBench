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
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  nvenc_lib ; 
 void* os_dlsym (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void *load_nv_func(const char *func)
{
	void *func_ptr = os_dlsym(nvenc_lib, func);
	if (!func_ptr) {
		error("Could not load function: %s", func);
	}
	return func_ptr;
}