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
 char* get_path (char const*,char const*) ; 
 int /*<<< orphan*/  os_rename (char*,char*) ; 
 int /*<<< orphan*/  os_unlink (char*) ; 

__attribute__((used)) static inline void replace_file(const char *src_base_path,
				const char *dst_base_path, const char *file)
{
	char *src_path = get_path(src_base_path, file);
	char *dst_path = get_path(dst_base_path, file);

	if (src_path && dst_path) {
		os_unlink(dst_path);
		os_rename(src_path, dst_path);
	}

	bfree(dst_path);
	bfree(src_path);
}