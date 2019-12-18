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
struct stat {unsigned long long st_size; int /*<<< orphan*/  st_mode; } ;
struct file {unsigned long long max_blocks; int /*<<< orphan*/  real_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKGETSIZE64 ; 
 unsigned long long BS ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 

__attribute__((used)) static int get_file_size(struct file *f)
{
	struct stat st;

	if (fstat(f->real_fd, &st) < 0)
		return -1;
	if (S_ISBLK(st.st_mode)) {
		unsigned long long bytes;

		if (ioctl(f->real_fd, BLKGETSIZE64, &bytes) != 0)
			return -1;

		f->max_blocks = bytes / BS;
		return 0;
	} else if (S_ISREG(st.st_mode)) {
		f->max_blocks = st.st_size / BS;
		return 0;
	}

	return -1;
}