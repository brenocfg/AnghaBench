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
struct pcxhr_mgr {TYPE_1__* pci; int /*<<< orphan*/  xlx_selmic; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCXHR_OUTPB (struct pcxhr_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCXHR_SELMIC_PHANTOM_ALIM ; 
 int /*<<< orphan*/  PCXHR_XLX_SELMIC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void hr222_phantom_power(struct pcxhr_mgr *mgr, int power)
{
	if (power)
		mgr->xlx_selmic |= PCXHR_SELMIC_PHANTOM_ALIM;
	else
		mgr->xlx_selmic &= ~PCXHR_SELMIC_PHANTOM_ALIM;

	PCXHR_OUTPB(mgr, PCXHR_XLX_SELMIC, mgr->xlx_selmic);

	dev_dbg(&mgr->pci->dev, "hr222_phantom_power : set %d\n", power);
}