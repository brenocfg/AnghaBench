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
 int /*<<< orphan*/  __tracing_path_set (char*,char const*) ; 
 char* tracefs__mount () ; 
 char const* tracing_path ; 

__attribute__((used)) static const char *tracing_path_tracefs_mount(void)
{
	const char *mnt;

	mnt = tracefs__mount();
	if (!mnt)
		return NULL;

	__tracing_path_set("", mnt);

	return tracing_path;
}