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
 scalar_t__ memcmp (char*,char*,int) ; 
 int read_tar_number (char*,int) ; 
 int tarChecksum (char*) ; 

bool
isValidTarHeader(char *header)
{
	int			sum;
	int			chk = tarChecksum(header);

	sum = read_tar_number(&header[148], 8);

	if (sum != chk)
		return false;

	/* POSIX tar format */
	if (memcmp(&header[257], "ustar\0", 6) == 0 &&
		memcmp(&header[263], "00", 2) == 0)
		return true;
	/* GNU tar format */
	if (memcmp(&header[257], "ustar  \0", 8) == 0)
		return true;
	/* not-quite-POSIX format written by pre-9.3 pg_dump */
	if (memcmp(&header[257], "ustar00\0", 8) == 0)
		return true;

	return false;
}