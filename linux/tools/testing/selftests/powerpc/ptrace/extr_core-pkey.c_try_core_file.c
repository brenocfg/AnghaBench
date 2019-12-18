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
struct stat {scalar_t__ st_mtime; int /*<<< orphan*/  st_size; } ;
struct shared_info {scalar_t__ core_time; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_FAIL ; 
 int stat (char const*,struct stat*) ; 

__attribute__((used)) static off_t try_core_file(const char *filename, struct shared_info *info,
			   pid_t pid)
{
	struct stat buf;
	int ret;

	ret = stat(filename, &buf);
	if (ret == -1)
		return TEST_FAIL;

	/* Make sure we're not using a stale core file. */
	return buf.st_mtime >= info->core_time ? buf.st_size : TEST_FAIL;
}