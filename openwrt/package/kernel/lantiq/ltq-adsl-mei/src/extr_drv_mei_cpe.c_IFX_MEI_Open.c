#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * private_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_rdev; } ;
typedef  TYPE_1__ DSL_DRV_inode_t ;
typedef  TYPE_2__ DSL_DRV_file_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DSL_BSP_DriverHandleGet (int,int) ; 
 int EIO ; 
 int /*<<< orphan*/  IFX_MEI_EMSG (char*,int,int) ; 
 int MAJOR (int /*<<< orphan*/ ) ; 
 int MINOR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
IFX_MEI_Open (DSL_DRV_inode_t * ino, DSL_DRV_file_t * fil)
{
	int maj = MAJOR (ino->i_rdev);
	int num = MINOR (ino->i_rdev);

	DSL_DEV_Device_t *pDev = NULL;
	if ((pDev = DSL_BSP_DriverHandleGet (maj, num)) == NULL) {
		IFX_MEI_EMSG("open(%d:%d) fail!\n", maj, num);
		return -EIO;
	}
	fil->private_data = pDev;
	return 0;
}