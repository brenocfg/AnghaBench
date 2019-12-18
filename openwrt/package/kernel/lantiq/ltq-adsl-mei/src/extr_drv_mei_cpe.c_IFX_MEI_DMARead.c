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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ CMV_RxMsg; } ;
typedef  int /*<<< orphan*/  DSL_DEV_MeiError_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_FAILURE ; 
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_SUCCESS ; 
 TYPE_1__* DSL_DEV_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_MEI_LongWordReadOffset (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  IFX_MEI_LongWordWriteOffset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  MEI_HALF_WORD_SWAP (int) ; 
 scalar_t__ ME_DX_AD ; 
 scalar_t__ ME_DX_DATA ; 

__attribute__((used)) static DSL_DEV_MeiError_t
IFX_MEI_DMARead (DSL_DEV_Device_t * pDev, u32 srcaddr, u32 * databuff,
		       u32 databuffsize)
{
	u32 *p = databuff;
	u32 temp;

	if (srcaddr & 3)
		return DSL_DEV_MEI_ERR_FAILURE;

	//      Set the read transfer address
	IFX_MEI_LongWordWriteOffset (pDev, (u32) ME_DX_AD, srcaddr);

	//      Read the data popped across DMA
	while (databuffsize--) {
		IFX_MEI_LongWordReadOffset (pDev, (u32) ME_DX_DATA, &temp);
		if (databuff == (u32 *) DSL_DEV_PRIVATE(pDev)->CMV_RxMsg)	// swap half word
			MEI_HALF_WORD_SWAP (temp);
		*p = temp;
		p++;
	}

	return DSL_DEV_MEI_ERR_SUCCESS;

}