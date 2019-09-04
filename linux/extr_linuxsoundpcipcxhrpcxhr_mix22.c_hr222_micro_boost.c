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
struct pcxhr_mgr {unsigned char xlx_selmic; TYPE_1__* pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCXHR_OUTPB (struct pcxhr_mgr*,int /*<<< orphan*/ ,unsigned char) ; 
 unsigned char PCXHR_SELMIC_PREAMPLI_MASK ; 
 int PCXHR_SELMIC_PREAMPLI_OFFSET ; 
 int /*<<< orphan*/  PCXHR_XLX_SELMIC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char) ; 

__attribute__((used)) static void hr222_micro_boost(struct pcxhr_mgr *mgr, int level)
{
	unsigned char boost_mask;
	boost_mask = (unsigned char) (level << PCXHR_SELMIC_PREAMPLI_OFFSET);
	if (boost_mask & (~PCXHR_SELMIC_PREAMPLI_MASK))
		return; /* only values form 0 to 3 accepted */

	mgr->xlx_selmic &= ~PCXHR_SELMIC_PREAMPLI_MASK;
	mgr->xlx_selmic |= boost_mask;

	PCXHR_OUTPB(mgr, PCXHR_XLX_SELMIC, mgr->xlx_selmic);

	dev_dbg(&mgr->pci->dev, "hr222_micro_boost : set %x\n", boost_mask);
}