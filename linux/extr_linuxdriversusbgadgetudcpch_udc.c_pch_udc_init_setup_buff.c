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
typedef  scalar_t__ u32 ;
struct pch_udc_stp_dma_desc {int /*<<< orphan*/  status; int /*<<< orphan*/  request; scalar_t__ reserved; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCH_UDC_BS_HST_RDY ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void pch_udc_init_setup_buff(struct pch_udc_stp_dma_desc *td_stp)
{
	static u32	pky_marker;

	if (!td_stp)
		return;
	td_stp->reserved = ++pky_marker;
	memset(&td_stp->request, 0xFF, sizeof td_stp->request);
	td_stp->status = PCH_UDC_BS_HST_RDY;
}