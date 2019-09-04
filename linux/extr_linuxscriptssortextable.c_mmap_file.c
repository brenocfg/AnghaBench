#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fail_file () ; 
 scalar_t__ fd_map ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ fstat (scalar_t__,TYPE_1__*) ; 
 void* mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int mmap_failed ; 
 scalar_t__ open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 TYPE_1__ sb ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void *mmap_file(char const *fname)
{
	void *addr;

	fd_map = open(fname, O_RDWR);
	if (fd_map < 0 || fstat(fd_map, &sb) < 0) {
		perror(fname);
		fail_file();
	}
	if (!S_ISREG(sb.st_mode)) {
		fprintf(stderr, "not a regular file: %s\n", fname);
		fail_file();
	}
	addr = mmap(0, sb.st_size, PROT_READ|PROT_WRITE, MAP_SHARED,
		    fd_map, 0);
	if (addr == MAP_FAILED) {
		mmap_failed = 1;
		fprintf(stderr, "Could not mmap file: %s\n", fname);
		fail_file();
	}
	return addr;
}