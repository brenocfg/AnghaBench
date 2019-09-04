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
struct TYPE_3__ {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  fail_file () ; 
 scalar_t__ fd_map ; 
 scalar_t__ file_end ; 
 scalar_t__ file_map ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ fstat (scalar_t__,TYPE_1__*) ; 
 scalar_t__ mmap (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int mmap_failed ; 
 scalar_t__ open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 TYPE_1__ sb ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ umalloc (scalar_t__) ; 
 int /*<<< orphan*/  uread (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void *mmap_file(char const *fname)
{
	fd_map = open(fname, O_RDONLY);
	if (fd_map < 0 || fstat(fd_map, &sb) < 0) {
		perror(fname);
		fail_file();
	}
	if (!S_ISREG(sb.st_mode)) {
		fprintf(stderr, "not a regular file: %s\n", fname);
		fail_file();
	}
	file_map = mmap(0, sb.st_size, PROT_READ|PROT_WRITE, MAP_PRIVATE,
			fd_map, 0);
	mmap_failed = 0;
	if (file_map == MAP_FAILED) {
		mmap_failed = 1;
		file_map = umalloc(sb.st_size);
		uread(fd_map, file_map, sb.st_size);
	}
	close(fd_map);

	file_end = file_map + sb.st_size;

	return file_map;
}