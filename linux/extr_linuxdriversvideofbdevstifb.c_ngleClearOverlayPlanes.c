#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int xres; int yres; } ;
struct TYPE_4__ {TYPE_1__ var; } ;
struct stifb_info {TYPE_2__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddrLong ; 
 int /*<<< orphan*/  BA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BAIndexBase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BAJustPoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BGx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BINovly ; 
 int /*<<< orphan*/  BitmapExtent08 ; 
 int /*<<< orphan*/  DataDynamic ; 
 int /*<<< orphan*/  FGx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_FIFO_SLOTS (struct stifb_info*,int,int) ; 
 int /*<<< orphan*/  IBOvals (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IndexedDcd ; 
 int /*<<< orphan*/  MaskAddrOffset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MaskOtc ; 
 int /*<<< orphan*/  NGLE_LOCK (struct stifb_info*) ; 
 int /*<<< orphan*/  NGLE_QUICK_SET_DST_BM_ACCESS (struct stifb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGLE_QUICK_SET_IMAGE_BITMAP_OP (struct stifb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGLE_REALLY_SET_IMAGE_FG_COLOR (struct stifb_info*,int) ; 
 int /*<<< orphan*/  NGLE_REALLY_SET_IMAGE_PLANEMASK (struct stifb_info*,int) ; 
 int /*<<< orphan*/  NGLE_SET_DSTXY (struct stifb_info*,int) ; 
 int /*<<< orphan*/  NGLE_SET_TRANSFERDATA (struct stifb_info*,int) ; 
 int /*<<< orphan*/  NGLE_UNLOCK (struct stifb_info*) ; 
 int /*<<< orphan*/  Otc04 ; 
 int /*<<< orphan*/  Ots08 ; 
 int /*<<< orphan*/  RopSrc ; 
 int /*<<< orphan*/  SET_LENXY_START_RECFILL (struct stifb_info*,int) ; 
 int /*<<< orphan*/  StaticReg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngleClearOverlayPlanes(struct stifb_info *fb, int mask, int data)
{
	int nFreeFifoSlots = 0;
	u32 packed_dst;
	u32 packed_len;
    
	NGLE_LOCK(fb);

	/* Hardware setup */
	GET_FIFO_SLOTS(fb, nFreeFifoSlots, 8);
	NGLE_QUICK_SET_DST_BM_ACCESS(fb, 
				     BA(IndexedDcd, Otc04, Ots08, AddrLong,
					BAJustPoint(0), BINovly, BAIndexBase(0)));

        NGLE_SET_TRANSFERDATA(fb, 0xffffffff);  /* Write foreground color */

        NGLE_REALLY_SET_IMAGE_FG_COLOR(fb, data);
        NGLE_REALLY_SET_IMAGE_PLANEMASK(fb, mask);
    
        packed_dst = 0;
        packed_len = (fb->info.var.xres << 16) | fb->info.var.yres;
        NGLE_SET_DSTXY(fb, packed_dst);
    
        /* Write zeroes to overlay planes */		       
	NGLE_QUICK_SET_IMAGE_BITMAP_OP(fb,
				       IBOvals(RopSrc, MaskAddrOffset(0),
					       BitmapExtent08, StaticReg(0),
					       DataDynamic, MaskOtc, BGx(0), FGx(0)));
		       
        SET_LENXY_START_RECFILL(fb, packed_len);

	NGLE_UNLOCK(fb);
}