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
typedef  void* u16 ;
struct brcms_hardware {int SRL; int LRL; int /*<<< orphan*/  d11core; scalar_t__ up; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int OBJADDR_SCR_SEL ; 
 int S_DOT11_LRC_LMT ; 
 int S_DOT11_SRC_LMT ; 
 int /*<<< orphan*/  bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  objaddr ; 
 int /*<<< orphan*/  objdata ; 

__attribute__((used)) static void brcms_b_retrylimit_upd(struct brcms_hardware *wlc_hw,
				   u16 SRL, u16 LRL)
{
	wlc_hw->SRL = SRL;
	wlc_hw->LRL = LRL;

	/* write retry limit to SCR, shouldn't need to suspend */
	if (wlc_hw->up) {
		bcma_write32(wlc_hw->d11core, D11REGOFFS(objaddr),
			     OBJADDR_SCR_SEL | S_DOT11_SRC_LMT);
		(void)bcma_read32(wlc_hw->d11core, D11REGOFFS(objaddr));
		bcma_write32(wlc_hw->d11core, D11REGOFFS(objdata), wlc_hw->SRL);
		bcma_write32(wlc_hw->d11core, D11REGOFFS(objaddr),
			     OBJADDR_SCR_SEL | S_DOT11_LRC_LMT);
		(void)bcma_read32(wlc_hw->d11core, D11REGOFFS(objaddr));
		bcma_write32(wlc_hw->d11core, D11REGOFFS(objdata), wlc_hw->LRL);
	}
}