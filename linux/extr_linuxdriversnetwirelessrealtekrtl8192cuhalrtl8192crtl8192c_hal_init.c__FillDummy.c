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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  VOID ;

/* Variables and functions */

__attribute__((used)) static VOID
_FillDummy(
	u8*		pFwBuf,
	u32*	pFwLen
	)
{
	u32	FwLen = *pFwLen;
	u8	remain = (u8)(FwLen%4);
	remain = (remain==0)?0:(4-remain);

	while(remain>0)
	{
		pFwBuf[FwLen] = 0;
		FwLen++;
		remain--;
	}

	*pFwLen = FwLen;
}