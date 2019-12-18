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
typedef  int ssize_t ;

/* Variables and functions */
 char* VERSION ; 
 scalar_t__ bigendian () ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  output_fd ; 
 char page_size ; 
 int strlen (char*) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int tracing_data_header(void)
{
	char buf[20];
	ssize_t size;

	/* just guessing this is someone's birthday.. ;) */
	buf[0] = 23;
	buf[1] = 8;
	buf[2] = 68;
	memcpy(buf + 3, "tracing", 7);

	if (write(output_fd, buf, 10) != 10)
		return -1;

	size = strlen(VERSION) + 1;
	if (write(output_fd, VERSION, size) != size)
		return -1;

	/* save endian */
	if (bigendian())
		buf[0] = 1;
	else
		buf[0] = 0;

	if (write(output_fd, buf, 1) != 1)
		return -1;

	/* save size of long */
	buf[0] = sizeof(long);
	if (write(output_fd, buf, 1) != 1)
		return -1;

	/* save page_size */
	if (write(output_fd, &page_size, 4) != 4)
		return -1;

	return 0;
}