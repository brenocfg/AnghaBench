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
struct mtd_oob_buf {int /*<<< orphan*/  ptr; int /*<<< orphan*/  length; int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  MEMREADOOB ; 
 int /*<<< orphan*/  TFFS_SECTOR_OOB_SIZE ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mtd_oob_buf*) ; 
 int /*<<< orphan*/  mtdfd ; 
 int /*<<< orphan*/  oobbuf ; 

__attribute__((used)) static int read_sectoroob(off_t pos)
{
	struct mtd_oob_buf oob = {
		.start = pos,
		.length = TFFS_SECTOR_OOB_SIZE,
		.ptr = oobbuf
	};

	if (ioctl(mtdfd, MEMREADOOB, &oob) < 0)	{
		return -1;
	}

	return 0;
}