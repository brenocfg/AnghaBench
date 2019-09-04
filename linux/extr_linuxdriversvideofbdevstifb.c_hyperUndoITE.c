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
typedef  int /*<<< orphan*/  u32 ;
struct stifb_info {int dummy; } ;

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
 int /*<<< orphan*/  NGLE_BINC_SET_DSTADDR (struct stifb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGLE_BINC_SET_DSTMASK (struct stifb_info*,int) ; 
 int /*<<< orphan*/  NGLE_BINC_WRITE32 (struct stifb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGLE_LOCK (struct stifb_info*) ; 
 int /*<<< orphan*/  NGLE_LONG_FB_ADDRESS (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGLE_QUICK_SET_DST_BM_ACCESS (struct stifb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGLE_QUICK_SET_IMAGE_BITMAP_OP (struct stifb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGLE_REALLY_SET_IMAGE_PLANEMASK (struct stifb_info*,int) ; 
 int /*<<< orphan*/  NGLE_UNLOCK (struct stifb_info*) ; 
 int /*<<< orphan*/  Otc04 ; 
 int /*<<< orphan*/  Ots08 ; 
 int /*<<< orphan*/  REG_32 ; 
 int /*<<< orphan*/  RopSrc ; 
 int /*<<< orphan*/  StaticReg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_WORD (int,struct stifb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hyperUndoITE(struct stifb_info *fb)
{
	int nFreeFifoSlots = 0;
	u32 fbAddr;

	NGLE_LOCK(fb);

	GET_FIFO_SLOTS(fb, nFreeFifoSlots, 1);
	WRITE_WORD(0xffffffff, fb, REG_32);

	/* Write overlay transparency mask so only entry 255 is transparent */

	/* Hardware setup for full-depth write to "magic" location */
	GET_FIFO_SLOTS(fb, nFreeFifoSlots, 7);
	NGLE_QUICK_SET_DST_BM_ACCESS(fb, 
		BA(IndexedDcd, Otc04, Ots08, AddrLong,
		BAJustPoint(0), BINovly, BAIndexBase(0)));
	NGLE_QUICK_SET_IMAGE_BITMAP_OP(fb,
		IBOvals(RopSrc, MaskAddrOffset(0),
		BitmapExtent08, StaticReg(0),
		DataDynamic, MaskOtc, BGx(0), FGx(0)));

	/* Now prepare to write to the "magic" location */
	fbAddr = NGLE_LONG_FB_ADDRESS(0, 1532, 0);
	NGLE_BINC_SET_DSTADDR(fb, fbAddr);
	NGLE_REALLY_SET_IMAGE_PLANEMASK(fb, 0xffffff);
	NGLE_BINC_SET_DSTMASK(fb, 0xffffffff);

	/* Finally, write a zero to clear the mask */
	NGLE_BINC_WRITE32(fb, 0);

	NGLE_UNLOCK(fb);
}