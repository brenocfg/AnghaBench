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
struct fsl_micfil {TYPE_1__* pdev; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MICFIL_CTRL2_CICOSR_MASK ; 
 int MICFIL_CTRL2_CICOSR_SHIFT ; 
 int MICFIL_CTRL2_QSEL_MASK ; 
#define  MICFIL_HIGH_QUALITY 133 
#define  MICFIL_LOW_QUALITY 132 
#define  MICFIL_MEDIUM_QUALITY 131 
#define  MICFIL_VLOW0_QUALITY 130 
#define  MICFIL_VLOW1_QUALITY 129 
#define  MICFIL_VLOW2_QUALITY 128 
 int /*<<< orphan*/  REG_MICFIL_CTRL2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline int get_pdm_clk(struct fsl_micfil *micfil,
			      unsigned int rate)
{
	u32 ctrl2_reg;
	int qsel, osr;
	int bclk;

	regmap_read(micfil->regmap, REG_MICFIL_CTRL2, &ctrl2_reg);
	osr = 16 - ((ctrl2_reg & MICFIL_CTRL2_CICOSR_MASK)
		    >> MICFIL_CTRL2_CICOSR_SHIFT);

	regmap_read(micfil->regmap, REG_MICFIL_CTRL2, &ctrl2_reg);
	qsel = ctrl2_reg & MICFIL_CTRL2_QSEL_MASK;

	switch (qsel) {
	case MICFIL_HIGH_QUALITY:
		bclk = rate * 8 * osr / 2; /* kfactor = 0.5 */
		break;
	case MICFIL_MEDIUM_QUALITY:
	case MICFIL_VLOW0_QUALITY:
		bclk = rate * 4 * osr * 1; /* kfactor = 1 */
		break;
	case MICFIL_LOW_QUALITY:
	case MICFIL_VLOW1_QUALITY:
		bclk = rate * 2 * osr * 2; /* kfactor = 2 */
		break;
	case MICFIL_VLOW2_QUALITY:
		bclk = rate * osr * 4; /* kfactor = 4 */
		break;
	default:
		dev_err(&micfil->pdev->dev,
			"Please make sure you select a valid quality.\n");
		bclk = -1;
		break;
	}

	return bclk;
}