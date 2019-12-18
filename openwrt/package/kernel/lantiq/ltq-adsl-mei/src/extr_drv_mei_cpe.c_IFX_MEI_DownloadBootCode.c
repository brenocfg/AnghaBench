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
typedef  int /*<<< orphan*/  DSL_DEV_MeiError_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_SUCCESS ; 
 int /*<<< orphan*/  IFX_MEI_DownloadBootPages (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_MEI_EnableCLK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_MEI_FuseProg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_MEI_IRQDisable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static DSL_DEV_MeiError_t
IFX_MEI_DownloadBootCode (DSL_DEV_Device_t *pDev)
{
	IFX_MEI_IRQDisable (pDev);

	IFX_MEI_EnableCLK (pDev);

	IFX_MEI_FuseProg (pDev);	//program fuse rar

	IFX_MEI_DownloadBootPages (pDev);

	return DSL_DEV_MEI_ERR_SUCCESS;
}