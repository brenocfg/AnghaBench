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
struct fs {char* name; char const** mounts; } ;

/* Variables and functions */
 scalar_t__ getenv (char*) ; 
 int /*<<< orphan*/  mem_toupper (char*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static const char *mount_overload(struct fs *fs)
{
	size_t name_len = strlen(fs->name);
	/* "PERF_" + name + "_ENVIRONMENT" + '\0' */
	char upper_name[5 + name_len + 12 + 1];

	snprintf(upper_name, name_len, "PERF_%s_ENVIRONMENT", fs->name);
	mem_toupper(upper_name, name_len);

	return getenv(upper_name) ?: *fs->mounts;
}