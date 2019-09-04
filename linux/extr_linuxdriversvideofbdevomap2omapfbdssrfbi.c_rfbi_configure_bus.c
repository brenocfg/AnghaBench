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
typedef  enum omap_rfbi_parallelmode { ____Placeholder_omap_rfbi_parallelmode } omap_rfbi_parallelmode ;
typedef  enum omap_rfbi_datatype { ____Placeholder_omap_rfbi_datatype } omap_rfbi_datatype ;
typedef  enum omap_rfbi_cycleformat { ____Placeholder_omap_rfbi_cycleformat } omap_rfbi_cycleformat ;
struct TYPE_2__ {int datatype; int parallelmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DSSDBG (char*,int,int,int,int,int) ; 
 int FLD_MOD (int,int,int,int) ; 
 int FLD_VAL (int,int,int) ; 
#define  OMAP_DSS_RFBI_CYCLEFORMAT_1_1 131 
#define  OMAP_DSS_RFBI_CYCLEFORMAT_2_1 130 
#define  OMAP_DSS_RFBI_CYCLEFORMAT_3_1 129 
#define  OMAP_DSS_RFBI_CYCLEFORMAT_3_2 128 
 int OMAP_DSS_RFBI_DATATYPE_12 ; 
 int OMAP_DSS_RFBI_DATATYPE_16 ; 
 int OMAP_DSS_RFBI_DATATYPE_18 ; 
 int OMAP_DSS_RFBI_DATATYPE_24 ; 
 int OMAP_DSS_RFBI_PARALLELMODE_12 ; 
 int OMAP_DSS_RFBI_PARALLELMODE_16 ; 
 int OMAP_DSS_RFBI_PARALLELMODE_8 ; 
 int OMAP_DSS_RFBI_PARALLELMODE_9 ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  RFBI_CONFIG (int) ; 
 int /*<<< orphan*/  RFBI_CONTROL ; 
 int /*<<< orphan*/  RFBI_DATA_CYCLE1 (int) ; 
 int /*<<< orphan*/  RFBI_DATA_CYCLE2 (int) ; 
 int /*<<< orphan*/  RFBI_DATA_CYCLE3 (int) ; 
 TYPE_1__ rfbi ; 
 int rfbi_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfbi_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rfbi_configure_bus(int rfbi_module, int bpp, int lines)
{
	u32 l;
	int cycle1 = 0, cycle2 = 0, cycle3 = 0;
	enum omap_rfbi_cycleformat cycleformat;
	enum omap_rfbi_datatype datatype;
	enum omap_rfbi_parallelmode parallelmode;

	switch (bpp) {
	case 12:
		datatype = OMAP_DSS_RFBI_DATATYPE_12;
		break;
	case 16:
		datatype = OMAP_DSS_RFBI_DATATYPE_16;
		break;
	case 18:
		datatype = OMAP_DSS_RFBI_DATATYPE_18;
		break;
	case 24:
		datatype = OMAP_DSS_RFBI_DATATYPE_24;
		break;
	default:
		BUG();
		return 1;
	}
	rfbi.datatype = datatype;

	switch (lines) {
	case 8:
		parallelmode = OMAP_DSS_RFBI_PARALLELMODE_8;
		break;
	case 9:
		parallelmode = OMAP_DSS_RFBI_PARALLELMODE_9;
		break;
	case 12:
		parallelmode = OMAP_DSS_RFBI_PARALLELMODE_12;
		break;
	case 16:
		parallelmode = OMAP_DSS_RFBI_PARALLELMODE_16;
		break;
	default:
		BUG();
		return 1;
	}
	rfbi.parallelmode = parallelmode;

	if ((bpp % lines) == 0) {
		switch (bpp / lines) {
		case 1:
			cycleformat = OMAP_DSS_RFBI_CYCLEFORMAT_1_1;
			break;
		case 2:
			cycleformat = OMAP_DSS_RFBI_CYCLEFORMAT_2_1;
			break;
		case 3:
			cycleformat = OMAP_DSS_RFBI_CYCLEFORMAT_3_1;
			break;
		default:
			BUG();
			return 1;
		}
	} else if ((2 * bpp % lines) == 0) {
		if ((2 * bpp / lines) == 3)
			cycleformat = OMAP_DSS_RFBI_CYCLEFORMAT_3_2;
		else {
			BUG();
			return 1;
		}
	} else {
		BUG();
		return 1;
	}

	switch (cycleformat) {
	case OMAP_DSS_RFBI_CYCLEFORMAT_1_1:
		cycle1 = lines;
		break;

	case OMAP_DSS_RFBI_CYCLEFORMAT_2_1:
		cycle1 = lines;
		cycle2 = lines;
		break;

	case OMAP_DSS_RFBI_CYCLEFORMAT_3_1:
		cycle1 = lines;
		cycle2 = lines;
		cycle3 = lines;
		break;

	case OMAP_DSS_RFBI_CYCLEFORMAT_3_2:
		cycle1 = lines;
		cycle2 = (lines / 2) | ((lines / 2) << 16);
		cycle3 = (lines << 16);
		break;
	}

	REG_FLD_MOD(RFBI_CONTROL, 0, 3, 2); /* clear CS */

	l = 0;
	l |= FLD_VAL(parallelmode, 1, 0);
	l |= FLD_VAL(0, 3, 2);		/* TRIGGERMODE: ITE */
	l |= FLD_VAL(0, 4, 4);		/* TIMEGRANULARITY */
	l |= FLD_VAL(datatype, 6, 5);
	/* l |= FLD_VAL(2, 8, 7); */	/* L4FORMAT, 2pix/L4 */
	l |= FLD_VAL(0, 8, 7);	/* L4FORMAT, 1pix/L4 */
	l |= FLD_VAL(cycleformat, 10, 9);
	l |= FLD_VAL(0, 12, 11);	/* UNUSEDBITS */
	l |= FLD_VAL(0, 16, 16);	/* A0POLARITY */
	l |= FLD_VAL(0, 17, 17);	/* REPOLARITY */
	l |= FLD_VAL(0, 18, 18);	/* WEPOLARITY */
	l |= FLD_VAL(0, 19, 19);	/* CSPOLARITY */
	l |= FLD_VAL(1, 20, 20);	/* TE_VSYNC_POLARITY */
	l |= FLD_VAL(1, 21, 21);	/* HSYNCPOLARITY */
	rfbi_write_reg(RFBI_CONFIG(rfbi_module), l);

	rfbi_write_reg(RFBI_DATA_CYCLE1(rfbi_module), cycle1);
	rfbi_write_reg(RFBI_DATA_CYCLE2(rfbi_module), cycle2);
	rfbi_write_reg(RFBI_DATA_CYCLE3(rfbi_module), cycle3);


	l = rfbi_read_reg(RFBI_CONTROL);
	l = FLD_MOD(l, rfbi_module+1, 3, 2); /* Select CSx */
	l = FLD_MOD(l, 0, 1, 1); /* clear bypass */
	rfbi_write_reg(RFBI_CONTROL, l);


	DSSDBG("RFBI config: bpp %d, lines %d, cycles: 0x%x 0x%x 0x%x\n",
	       bpp, lines, cycle1, cycle2, cycle3);

	return 0;
}