#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t st_size; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__ fd_map ; 
 int /*<<< orphan*/  file_append ; 
 size_t file_append_size ; 
 int /*<<< orphan*/  file_map ; 
 int /*<<< orphan*/  file_updated ; 
 scalar_t__ open (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 scalar_t__ rename (char*,char const*) ; 
 TYPE_1__ sb ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 size_t write (scalar_t__,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int write_file(const char *fname)
{
	char tmp_file[strlen(fname) + 4];
	size_t n;

	if (!file_updated)
		return 0;

	sprintf(tmp_file, "%s.rc", fname);

	/*
	 * After reading the entire file into memory, delete it
	 * and write it back, to prevent weird side effects of modifying
	 * an object file in place.
	 */
	fd_map = open(tmp_file, O_WRONLY | O_TRUNC | O_CREAT, sb.st_mode);
	if (fd_map < 0) {
		perror(fname);
		return -1;
	}
	n = write(fd_map, file_map, sb.st_size);
	if (n != sb.st_size) {
		perror("write");
		close(fd_map);
		return -1;
	}
	if (file_append_size) {
		n = write(fd_map, file_append, file_append_size);
		if (n != file_append_size) {
			perror("write");
			close(fd_map);
			return -1;
		}
	}
	close(fd_map);
	if (rename(tmp_file, fname) < 0) {
		perror(fname);
		return -1;
	}
	return 0;
}