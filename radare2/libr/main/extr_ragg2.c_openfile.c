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
 int O_CREAT ; 
 int O_RDWR ; 
 int _chsize (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  fchmod (int,int) ; 
 int ftruncate (int,int /*<<< orphan*/ ) ; 
 int open (char const*,int,...) ; 

__attribute__((used)) static int openfile(const char *f, int x) {
	int fd = open (f, O_RDWR | O_CREAT, 0644);
	if (fd == -1) {
		fd = open (f, O_RDWR);
		if (fd == -1) {
			return -1;
		}
	}
#if __UNIX__
	if (x) {
		fchmod (fd, 0755);
	}
#endif
#if _MSC_VER
	int r = _chsize (fd, 0);
#else
	int r = ftruncate (fd, 0);
#endif
	if (r != 0) {
		eprintf ("Could not resize\n");
	}
	close (1);
	dup2 (fd, 1);
	return fd;
}