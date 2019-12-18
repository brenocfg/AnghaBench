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
struct statfs {int f_type; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  dirfd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long) ; 
 int fstatfs (int /*<<< orphan*/ ,struct statfs*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(void)
{
	DIR *d;
	struct statfs sfs;

	d = opendir("/proc");
	if (!d)
		return 4;

	/* Ensure /proc is proc. */
	if (fstatfs(dirfd(d), &sfs) == -1) {
		return 1;
	}
	if (sfs.f_type != 0x9fa0) {
		fprintf(stderr, "error: unexpected f_type %lx\n", (long)sfs.f_type);
		return 2;
	}

	f(d, 0);

	return 0;
}