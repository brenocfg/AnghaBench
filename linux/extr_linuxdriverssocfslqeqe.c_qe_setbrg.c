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
typedef  enum qe_clock { ____Placeholder_qe_clock } qe_clock ;
struct TYPE_3__ {int /*<<< orphan*/ * brgc; } ;
struct TYPE_4__ {TYPE_1__ brg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PVR_VER_832x ; 
 int /*<<< orphan*/  PVR_VER_836x ; 
 int QE_BRG1 ; 
 int QE_BRG16 ; 
 int QE_BRGC_DIV16 ; 
 int QE_BRGC_DIVISOR_MAX ; 
 int QE_BRGC_DIVISOR_SHIFT ; 
 int QE_BRGC_ENABLE ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pvr_version_is (int /*<<< orphan*/ ) ; 
 unsigned int qe_get_brg_clk () ; 
 TYPE_2__* qe_immr ; 

int qe_setbrg(enum qe_clock brg, unsigned int rate, unsigned int multiplier)
{
	u32 divisor, tempval;
	u32 div16 = 0;

	if ((brg < QE_BRG1) || (brg > QE_BRG16))
		return -EINVAL;

	divisor = qe_get_brg_clk() / (rate * multiplier);

	if (divisor > QE_BRGC_DIVISOR_MAX + 1) {
		div16 = QE_BRGC_DIV16;
		divisor /= 16;
	}

	/* Errata QE_General4, which affects some MPC832x and MPC836x SOCs, says
	   that the BRG divisor must be even if you're not using divide-by-16
	   mode. */
	if (pvr_version_is(PVR_VER_836x) || pvr_version_is(PVR_VER_832x))
		if (!div16 && (divisor & 1) && (divisor > 3))
			divisor++;

	tempval = ((divisor - 1) << QE_BRGC_DIVISOR_SHIFT) |
		QE_BRGC_ENABLE | div16;

	out_be32(&qe_immr->brg.brgc[brg - QE_BRG1], tempval);

	return 0;
}