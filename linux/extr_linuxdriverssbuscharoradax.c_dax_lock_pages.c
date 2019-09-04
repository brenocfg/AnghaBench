#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct dax_ctx {int /*<<< orphan*/ ** pages; struct dax_ccb* ccb_buf; } ;
struct TYPE_2__ {scalar_t__ out_addr_type; scalar_t__ pri_addr_type; scalar_t__ sec_addr_type; scalar_t__ table_addr_type; scalar_t__ longccb; } ;
struct dax_ccb {TYPE_1__ hdr; scalar_t__ tbl; scalar_t__ sec; scalar_t__ pri; scalar_t__ out; } ;

/* Variables and functions */
 scalar_t__ DAX_ADDR_TYPE_VA ; 
 void* DAX_ADDR_TYPE_VA_ALT ; 
 int DAX_SUBMIT_ERR_NOACCESS ; 
 int DAX_SUBMIT_OK ; 
 size_t OUT ; 
 size_t PRI ; 
 size_t SEC ; 
 size_t TBL ; 
 int /*<<< orphan*/  dax_dbg (char*) ; 
 scalar_t__ dax_lock_page (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dax_unlock_pages (struct dax_ctx*,int,int) ; 

__attribute__((used)) static int dax_lock_pages(struct dax_ctx *ctx, int idx,
			  int nelem, u64 *err_va)
{
	int i;

	for (i = 0; i < nelem; i++) {
		struct dax_ccb *ccbp = &ctx->ccb_buf[i];

		/*
		 * For each address in the CCB whose type is virtual,
		 * lock the page and change the type to virtual alternate
		 * context. On error, return the offending address in
		 * err_va.
		 */
		if (ccbp->hdr.out_addr_type == DAX_ADDR_TYPE_VA) {
			dax_dbg("output");
			if (dax_lock_page(ccbp->out,
					  &ctx->pages[i + idx][OUT]) != 0) {
				*err_va = (u64)ccbp->out;
				goto error;
			}
			ccbp->hdr.out_addr_type = DAX_ADDR_TYPE_VA_ALT;
		}

		if (ccbp->hdr.pri_addr_type == DAX_ADDR_TYPE_VA) {
			dax_dbg("input");
			if (dax_lock_page(ccbp->pri,
					  &ctx->pages[i + idx][PRI]) != 0) {
				*err_va = (u64)ccbp->pri;
				goto error;
			}
			ccbp->hdr.pri_addr_type = DAX_ADDR_TYPE_VA_ALT;
		}

		if (ccbp->hdr.sec_addr_type == DAX_ADDR_TYPE_VA) {
			dax_dbg("sec input");
			if (dax_lock_page(ccbp->sec,
					  &ctx->pages[i + idx][SEC]) != 0) {
				*err_va = (u64)ccbp->sec;
				goto error;
			}
			ccbp->hdr.sec_addr_type = DAX_ADDR_TYPE_VA_ALT;
		}

		if (ccbp->hdr.table_addr_type == DAX_ADDR_TYPE_VA) {
			dax_dbg("tbl");
			if (dax_lock_page(ccbp->tbl,
					  &ctx->pages[i + idx][TBL]) != 0) {
				*err_va = (u64)ccbp->tbl;
				goto error;
			}
			ccbp->hdr.table_addr_type = DAX_ADDR_TYPE_VA_ALT;
		}

		/* skip over 2nd 64 bytes of long CCB */
		if (ccbp->hdr.longccb)
			i++;
	}
	return DAX_SUBMIT_OK;

error:
	dax_unlock_pages(ctx, idx, nelem);
	return DAX_SUBMIT_ERR_NOACCESS;
}