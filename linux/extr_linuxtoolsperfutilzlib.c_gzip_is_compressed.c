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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ memcmp (char*,int const*,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 

bool gzip_is_compressed(const char *input)
{
	int fd = open(input, O_RDONLY);
	const uint8_t magic[2] = { 0x1f, 0x8b };
	char buf[2] = { 0 };
	ssize_t rc;

	if (fd < 0)
		return -1;

	rc = read(fd, buf, sizeof(buf));
	close(fd);
	return rc == sizeof(buf) ?
	       memcmp(buf, magic, sizeof(buf)) == 0 : false;
}