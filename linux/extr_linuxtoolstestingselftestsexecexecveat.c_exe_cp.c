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
struct stat {int /*<<< orphan*/  st_size; } ;

/* Variables and functions */
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 int open (char const*,int,int) ; 
 int open_or_die (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sendfile (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exe_cp(const char *src, const char *dest)
{
	int in_fd = open_or_die(src, O_RDONLY);
	int out_fd = open(dest, O_RDWR|O_CREAT|O_TRUNC, 0755);
	struct stat info;

	fstat(in_fd, &info);
	sendfile(out_fd, in_fd, NULL, info.st_size);
	close(in_fd);
	close(out_fd);
}