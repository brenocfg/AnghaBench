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
typedef  int /*<<< orphan*/  DSL_DRV_file_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 long EIO ; 
 int /*<<< orphan*/ * IFX_BSP_HandleGet (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFX_MEI_Ioctls (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 

__attribute__((used)) static long
IFX_MEI_UserIoctls (DSL_DRV_file_t * fil,
			  unsigned int command, unsigned long lon)
{
	int error = 0;
	DSL_DEV_Device_t *pDev;

	pDev = IFX_BSP_HandleGet (0, 0);
	if (pDev == NULL)
		return -EIO;

	error = IFX_MEI_Ioctls (pDev, 0, command, lon);
	return error;
}