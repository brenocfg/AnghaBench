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
 void* base_get_proc (char const*) ; 
 void* wgl_get_proc (char const*) ; 

__attribute__((used)) static inline void *get_proc(const char *name)
{
	void *func = wgl_get_proc(name);
	if (!func)
		func = base_get_proc(name);

	return func;
}