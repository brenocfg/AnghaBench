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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SYSFS_PATH ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,int,...) ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int read (int,int*,int) ; 

void read_ec_val(int fd, int byte_offset)
{
	uint8_t buf;
	int error;

	error = lseek(fd, byte_offset, SEEK_SET);
	if (error != byte_offset)
		err(EXIT_FAILURE, "Cannot set offset to 0x%.2x", byte_offset);

	error = read(fd, &buf, 1);
	if (error != 1)
		err(EXIT_FAILURE, "Could not read byte 0x%.2x from %s\n",
		    byte_offset, SYSFS_PATH);
	printf("0x%.2x\n", buf);
	return;
}