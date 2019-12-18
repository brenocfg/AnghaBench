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
 scalar_t__ DEFAULT_XLOG_SEG_SIZE ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  filename ; 
 scalar_t__ fsync (int) ; 
 int /*<<< orphan*/  full_buf ; 
 int needs_unlink ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ write (int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
test_open(void)
{
	int			tmpfile;

	/*
	 * test if we can open the target file
	 */
	if ((tmpfile = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
		die("could not open output file");
	needs_unlink = 1;
	if (write(tmpfile, full_buf, DEFAULT_XLOG_SEG_SIZE) !=
		DEFAULT_XLOG_SEG_SIZE)
		die("write failed");

	/* fsync now so that dirty buffers don't skew later tests */
	if (fsync(tmpfile) != 0)
		die("fsync failed");

	close(tmpfile);
}