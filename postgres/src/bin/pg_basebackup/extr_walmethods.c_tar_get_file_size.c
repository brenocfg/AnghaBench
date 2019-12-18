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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  tar_clear_error () ; 

__attribute__((used)) static ssize_t
tar_get_file_size(const char *pathname)
{
	tar_clear_error();

	/* Currently not used, so not supported */
	errno = ENOSYS;
	return -1;
}