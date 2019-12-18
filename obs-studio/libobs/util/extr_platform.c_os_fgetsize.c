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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int errno ; 
 int fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ os_fseeki64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int os_ftelli64 (int /*<<< orphan*/ *) ; 

int64_t os_fgetsize(FILE *file)
{
	int64_t cur_offset = os_ftelli64(file);
	int64_t size;
	int errval = 0;

	if (fseek(file, 0, SEEK_END) == -1)
		return -1;

	size = os_ftelli64(file);
	if (size == -1)
		errval = errno;

	if (os_fseeki64(file, cur_offset, SEEK_SET) != 0 && errval != 0)
		errno = errval;

	return size;
}