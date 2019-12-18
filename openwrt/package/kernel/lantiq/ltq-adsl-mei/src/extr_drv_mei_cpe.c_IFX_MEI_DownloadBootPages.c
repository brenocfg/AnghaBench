#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {TYPE_2__* img_hdr; } ;
struct TYPE_5__ {int count; TYPE_1__* page; } ;
struct TYPE_4__ {int p_size; int d_size; } ;
typedef  int /*<<< orphan*/  DSL_DEV_MeiError_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int BOOT_FLAG ; 
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_SUCCESS ; 
 TYPE_3__* DSL_DEV_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_DATA ; 
 int /*<<< orphan*/  GET_PROG ; 
 int /*<<< orphan*/  IFX_MEI_DMAWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int IFX_MEI_GetPage (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAXSWAPSIZE ; 
 int /*<<< orphan*/  mei_arc_swap_buff ; 

__attribute__((used)) static DSL_DEV_MeiError_t
IFX_MEI_DownloadBootPages (DSL_DEV_Device_t * pDev)
{
	int boot_loop;
	int page_size;
	u32 dest_addr;

	/*
	 **     DMA the boot code page(s)
	 */

	for (boot_loop = 1;
	     boot_loop <
	     (DSL_DEV_PRIVATE(pDev)->img_hdr-> count); boot_loop++) {
		if ((DSL_DEV_PRIVATE(pDev)-> img_hdr->page[boot_loop].p_size) & BOOT_FLAG) {
			page_size = IFX_MEI_GetPage (pDev, boot_loop,
						       GET_PROG, MAXSWAPSIZE,
						       mei_arc_swap_buff,
						       &dest_addr);
			if (page_size > 0) {
				IFX_MEI_DMAWrite (pDev, dest_addr,
							mei_arc_swap_buff,
							page_size);
			}
		}
		if ((DSL_DEV_PRIVATE(pDev)-> img_hdr->page[boot_loop].d_size) & BOOT_FLAG) {
			page_size = IFX_MEI_GetPage (pDev, boot_loop,
						       GET_DATA, MAXSWAPSIZE,
						       mei_arc_swap_buff,
						       &dest_addr);
			if (page_size > 0) {
				IFX_MEI_DMAWrite (pDev, dest_addr,
							mei_arc_swap_buff,
							page_size);
			}
		}
	}
	return DSL_DEV_MEI_ERR_SUCCESS;
}