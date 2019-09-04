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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,int,...) ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int write (int,int /*<<< orphan*/ *,int) ; 

void write_ec_val(int fd, int byte_offset, uint8_t value)
{
	int error;

	error = lseek(fd, byte_offset, SEEK_SET);
	if (error != byte_offset)
		err(EXIT_FAILURE, "Cannot set offset to 0x%.2x", byte_offset);

	error = write(fd, &value, 1);
	if (error != 1)
		err(EXIT_FAILURE, "Cannot write value 0x%.2x to offset 0x%.2x",
		    value, byte_offset);
}