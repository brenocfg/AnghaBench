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
struct ptd {void* faddr; void* len; void* mps; void* count; } ;
struct isp116x_ep {int /*<<< orphan*/  data; int /*<<< orphan*/  length; struct isp116x_ep* active; struct ptd ptd; } ;
struct isp116x {scalar_t__ atl_last_dir; int atl_buflen; int atl_bufshrt; struct isp116x_ep* atl_active; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  HCATLPORT ; 
 int /*<<< orphan*/  HCXFERCTR ; 
 int /*<<< orphan*/  HCuPINT ; 
 int HCuPINT_AIIEOT ; 
 scalar_t__ PTD_DIR_IN ; 
 int /*<<< orphan*/  dump_ptd (struct ptd*) ; 
 int /*<<< orphan*/  dump_ptd_in_data (struct ptd*,int /*<<< orphan*/ ) ; 
 void* isp116x_read_data16 (struct isp116x*) ; 
 int /*<<< orphan*/  isp116x_write_addr (struct isp116x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp116x_write_reg16 (struct isp116x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_ptddata_from_fifo (struct isp116x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unpack_fifo(struct isp116x *isp116x)
{
	struct isp116x_ep *ep;
	struct ptd *ptd;
	int buflen = isp116x->atl_last_dir == PTD_DIR_IN
	    ? isp116x->atl_buflen : isp116x->atl_bufshrt;

	isp116x_write_reg16(isp116x, HCuPINT, HCuPINT_AIIEOT);
	isp116x_write_reg16(isp116x, HCXFERCTR, buflen);
	isp116x_write_addr(isp116x, HCATLPORT);
	for (ep = isp116x->atl_active; ep; ep = ep->active) {
		ptd = &ep->ptd;
		ptd->count = isp116x_read_data16(isp116x);
		ptd->mps = isp116x_read_data16(isp116x);
		ptd->len = isp116x_read_data16(isp116x);
		ptd->faddr = isp116x_read_data16(isp116x);
		buflen -= sizeof(struct ptd);
		/* Skip reading data for last Setup or Out PTD */
		if (ep->active || (isp116x->atl_last_dir == PTD_DIR_IN)) {
			read_ptddata_from_fifo(isp116x, ep->data, ep->length);
			buflen -= ALIGN(ep->length, 4);
		}
		dump_ptd(ptd);
		dump_ptd_in_data(ptd, ep->data);
	}
	BUG_ON(buflen);
}