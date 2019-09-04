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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rio_mport {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  RIO_DEV_ID_CAR ; 
 int RIO_MAX_CHK_RETRY ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ rio_mport_read_config_32 (struct rio_mport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
rio_mport_chk_dev_access(struct rio_mport *mport, u16 destid, u8 hopcount)
{
	int i = 0;
	u32 tmp;

	while (rio_mport_read_config_32(mport, destid, hopcount,
					RIO_DEV_ID_CAR, &tmp)) {
		i++;
		if (i == RIO_MAX_CHK_RETRY)
			return -EIO;
		mdelay(1);
	}

	return 0;
}