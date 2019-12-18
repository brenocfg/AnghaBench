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
struct clk {int dummy; } ;
struct TYPE_4__ {TYPE_1__* port; } ;
struct TYPE_3__ {unsigned int tx_max_cell_rate; } ;

/* Variables and functions */
 int ATM_PORT_NUMBER ; 
 int /*<<< orphan*/ * QSB_CFG ; 
 int /*<<< orphan*/  QSB_CFG_TSTEPC_SET (int) ; 
 int /*<<< orphan*/ * QSB_ICDV ; 
 int /*<<< orphan*/  QSB_ICDV_TAU_SET (int /*<<< orphan*/ ) ; 
 int* QSB_RAMAC ; 
 int /*<<< orphan*/  QSB_RAMAC_LH_LOW ; 
 int QSB_RAMAC_LH_SET (int /*<<< orphan*/ ) ; 
 int QSB_RAMAC_RW_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QSB_RAMAC_RW_WRITE ; 
 int QSB_RAMAC_TESEL_SET (int) ; 
 int /*<<< orphan*/  QSB_RAMAC_TSEL_SCT ; 
 int QSB_RAMAC_TSEL_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QSB_RAMAC_TSEL_SPT ; 
 int /*<<< orphan*/ * QSB_RTD ; 
 int /*<<< orphan*/  QSB_RTD_TTV_SET (unsigned int) ; 
 int /*<<< orphan*/ * QSB_RTM ; 
 int /*<<< orphan*/  QSB_RTM_DM_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * QSB_SBL ; 
 int /*<<< orphan*/  QSB_SBL_SBL_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QSB_SET_SCT_MASK ; 
 int /*<<< orphan*/  QSB_SET_SPT_MASK ; 
 unsigned int QSB_SPT_INTRATE_SET (unsigned int) ; 
 unsigned int QSB_SPT_PN_SET (int) ; 
 unsigned int QSB_SPT_SBV_VALID ; 
 struct clk* clk_get_fpi () ; 
 unsigned int clk_get_rate (struct clk*) ; 
 TYPE_2__ g_atm_priv_data ; 
 int /*<<< orphan*/  qsb_srvm ; 
 int /*<<< orphan*/  qsb_tau ; 
 int qsb_tstep ; 

__attribute__((used)) static void qsb_global_set(void)
{
	struct clk *fpi_clk = clk_get_fpi();
	unsigned int qsb_clk = clk_get_rate(fpi_clk);
	int i;
	unsigned int tmp1, tmp2, tmp3;

	*QSB_ICDV = QSB_ICDV_TAU_SET(qsb_tau);
	*QSB_SBL  = QSB_SBL_SBL_SET(qsb_srvm);
	*QSB_CFG  = QSB_CFG_TSTEPC_SET(qsb_tstep >> 1);

	/*
	 *  set SCT and SPT per port
	 */
	for ( i = 0; i < ATM_PORT_NUMBER; i++ ) {
		if ( g_atm_priv_data.port[i].tx_max_cell_rate != 0 ) {
			tmp1 = ((qsb_clk * qsb_tstep) >> 1) / g_atm_priv_data.port[i].tx_max_cell_rate;
			tmp2 = tmp1 >> 6;                   /*  integer value of Tsb    */
			tmp3 = (tmp1 & ((1 << 6) - 1)) + 1; /*  fractional part of Tsb  */
			/*  carry over to integer part (?)  */
			if ( tmp3 == (1 << 6) ) {
				tmp3 = 0;
				tmp2++;
			}
			if ( tmp2 == 0 )
				tmp2 = tmp3 = 1;
			/*  1. set mask                                 */
			/*  2. write value to data transfer register    */
			/*  3. start the tranfer                        */
			/*  SCT (FracRate)  */
			*QSB_RTM   = QSB_RTM_DM_SET(QSB_SET_SCT_MASK);
			*QSB_RTD   = QSB_RTD_TTV_SET(tmp3);
			*QSB_RAMAC = QSB_RAMAC_RW_SET(QSB_RAMAC_RW_WRITE) |
					QSB_RAMAC_TSEL_SET(QSB_RAMAC_TSEL_SCT) |
					QSB_RAMAC_LH_SET(QSB_RAMAC_LH_LOW) |
					QSB_RAMAC_TESEL_SET(i & 0x01);
			/*  SPT (SBV + PN + IntRage)    */
			*QSB_RTM   = QSB_RTM_DM_SET(QSB_SET_SPT_MASK);
			*QSB_RTD   = QSB_RTD_TTV_SET(QSB_SPT_SBV_VALID | QSB_SPT_PN_SET(i & 0x01) | QSB_SPT_INTRATE_SET(tmp2));
			*QSB_RAMAC = QSB_RAMAC_RW_SET(QSB_RAMAC_RW_WRITE) |
				QSB_RAMAC_TSEL_SET(QSB_RAMAC_TSEL_SPT) |
				QSB_RAMAC_LH_SET(QSB_RAMAC_LH_LOW) |
				QSB_RAMAC_TESEL_SET(i & 0x01);
		}
	}
}