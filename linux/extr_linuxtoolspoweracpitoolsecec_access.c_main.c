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
 int EC_SPACE_SIZE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SYSFS_PATH ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dump_ec (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_opts (int,char**) ; 
 int read_byte_offset ; 
 int /*<<< orphan*/  read_ec_val (int,int) ; 
 int read_mode ; 
 int /*<<< orphan*/  usage (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_byte_offset ; 
 int /*<<< orphan*/  write_ec_val (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_value ; 

int main(int argc, char *argv[])
{
	int file_mode = O_RDONLY;
	int fd;

	parse_opts(argc, argv);

	if (read_mode == 0)
		file_mode = O_WRONLY;
	else if (read_mode == 1)
		file_mode = O_RDONLY;
	else
		usage(argv[0], EXIT_FAILURE);

	fd = open(SYSFS_PATH, file_mode);
	if (fd == -1)
		err(EXIT_FAILURE, "%s", SYSFS_PATH);

	if (read_mode)
		if (read_byte_offset == -1)
			dump_ec(fd);
		else if (read_byte_offset < 0 ||
			 read_byte_offset >= EC_SPACE_SIZE)
			usage(argv[0], EXIT_FAILURE);
		else
			read_ec_val(fd, read_byte_offset);
	else
		write_ec_val(fd, write_byte_offset, write_value);
	close(fd);

	exit(EXIT_SUCCESS);
}