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
typedef  int /*<<< orphan*/  gdIOCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ReadOK (int /*<<< orphan*/ *,unsigned char*,unsigned char) ; 

__attribute__((used)) static int
GetDataBlock_(gdIOCtx *fd, unsigned char *buf, int *ZeroDataBlockP)
{
	unsigned char   count;

	if (! ReadOK(fd,&count,1)) {
		return -1;
	}

	*ZeroDataBlockP = count == 0;

	if ((count != 0) && (! ReadOK(fd, buf, count))) {
		return -1;
	}

	return count;
}