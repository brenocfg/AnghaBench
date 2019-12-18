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
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int fd_map ; 
 void* file_end ; 
 void* file_map ; 
 int /*<<< orphan*/ * file_ptr ; 
 scalar_t__ file_updated ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ fstat (int,TYPE_1__*) ; 
 void* mmap (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mmap_failed ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 scalar_t__ read (int,void*,scalar_t__) ; 
 TYPE_1__ sb ; 
 int /*<<< orphan*/  stderr ; 
 void* umalloc (scalar_t__) ; 

__attribute__((used)) static void *mmap_file(char const *fname)
{
	/* Avoid problems if early cleanup() */
	fd_map = -1;
	mmap_failed = 1;
	file_map = NULL;
	file_ptr = NULL;
	file_updated = 0;
	sb.st_size = 0;

	fd_map = open(fname, O_RDONLY);
	if (fd_map < 0) {
		perror(fname);
		return NULL;
	}
	if (fstat(fd_map, &sb) < 0) {
		perror(fname);
		goto out;
	}
	if (!S_ISREG(sb.st_mode)) {
		fprintf(stderr, "not a regular file: %s\n", fname);
		goto out;
	}
	file_map = mmap(0, sb.st_size, PROT_READ|PROT_WRITE, MAP_PRIVATE,
			fd_map, 0);
	if (file_map == MAP_FAILED) {
		mmap_failed = 1;
		file_map = umalloc(sb.st_size);
		if (!file_map) {
			perror(fname);
			goto out;
		}
		if (read(fd_map, file_map, sb.st_size) != sb.st_size) {
			perror(fname);
			free(file_map);
			file_map = NULL;
			goto out;
		}
	} else
		mmap_failed = 0;
out:
	close(fd_map);
	fd_map = -1;

	file_end = file_map + sb.st_size;

	return file_map;
}