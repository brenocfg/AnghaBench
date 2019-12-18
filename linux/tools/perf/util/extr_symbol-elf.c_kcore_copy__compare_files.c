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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int kcore_copy__compare_fds (int,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kcore_copy__compare_files(const char *from_filename,
				     const char *to_filename)
{
	int from, to, err = -1;

	from = open(from_filename, O_RDONLY);
	if (from < 0)
		return -1;

	to = open(to_filename, O_RDONLY);
	if (to < 0)
		goto out_close_from;

	err = kcore_copy__compare_fds(from, to);

	close(to);
out_close_from:
	close(from);
	return err;
}