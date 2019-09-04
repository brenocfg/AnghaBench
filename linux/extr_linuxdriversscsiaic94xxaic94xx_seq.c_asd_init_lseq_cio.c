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
typedef  int u8 ;
struct asd_ha_struct {TYPE_2__* phys; } ;
struct TYPE_4__ {TYPE_1__* phy_desc; } ;
struct TYPE_3__ {int* sas_addr; } ;

/* Variables and functions */
 int ASD_SATA_INTERLOCK_TIMEOUT ; 
 int EN_ARP2HALTC ; 
 int LEDMODE_TXRX ; 
 int LEDTIMER ; 
 int LEDTIMERS_100ms ; 
 scalar_t__ LmARP2INTCTL (int) ; 
 int /*<<< orphan*/  LmARP2INTEN (int) ; 
 int /*<<< orphan*/  LmBITL_TIMER (int) ; 
 int LmBLIND48 ; 
 int /*<<< orphan*/  LmCONTROL (int) ; 
 int /*<<< orphan*/  LmFRMERREN (int) ; 
 int LmFRMERREN_MASK ; 
 scalar_t__ LmHWTSTAT (int) ; 
 scalar_t__ LmHWTSTATEN (int) ; 
 int LmHWTSTATEN_MASK ; 
 int LmM0INTEN_MASK ; 
 int LmM1INTEN_MASK ; 
 scalar_t__ LmM1SASALIGN (int) ; 
 scalar_t__ LmM1STPALIGN (int) ; 
 int LmM2INTEN_MASK ; 
 int /*<<< orphan*/  LmM3INTVEC0 (int) ; 
 int /*<<< orphan*/  LmM3INTVEC1 (int) ; 
 int /*<<< orphan*/  LmM3INTVEC10 (int) ; 
 int /*<<< orphan*/  LmM3INTVEC2 (int) ; 
 int /*<<< orphan*/  LmM3INTVEC3 (int) ; 
 int /*<<< orphan*/  LmM3INTVEC4 (int) ; 
 int /*<<< orphan*/  LmM3INTVEC5 (int) ; 
 int /*<<< orphan*/  LmM3INTVEC6 (int) ; 
 int /*<<< orphan*/  LmM3INTVEC7 (int) ; 
 int /*<<< orphan*/  LmM3INTVEC8 (int) ; 
 int /*<<< orphan*/  LmM3INTVEC9 (int) ; 
 int /*<<< orphan*/  LmM3SATATIMER (int) ; 
 int LmM5INTEN_MASK ; 
 int /*<<< orphan*/  LmMODECTL (int) ; 
 int LmMnBUFPERR ; 
 scalar_t__ LmMnBUFSTAT (int,int /*<<< orphan*/ ) ; 
 scalar_t__ LmMnDMAERRS (int,int) ; 
 int /*<<< orphan*/  LmMnFRMERR (int,int /*<<< orphan*/ ) ; 
 scalar_t__ LmMnHOLDLVL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LmMnINT (int,int) ; 
 int /*<<< orphan*/  LmMnINTEN (int,int) ; 
 scalar_t__ LmMnSATAFS (int,int) ; 
 scalar_t__ LmMnSCRATCHPAGE (int,int) ; 
 scalar_t__ LmMnSGDMAERRS (int,int) ; 
 scalar_t__ LmMnXFRLVL (int,int) ; 
 int LmMnXFRLVL_256 ; 
 int LmMnXFRLVL_512 ; 
 scalar_t__ LmMnXMTSIZE (int,int) ; 
 int /*<<< orphan*/  LmPRGMCNT (int) ; 
 int /*<<< orphan*/  LmPRIMSTAT0EN (int) ; 
 int LmPRIMSTAT0EN_MASK ; 
 int /*<<< orphan*/  LmPRIMSTAT1EN (int) ; 
 int LmPRIMSTAT1EN_MASK ; 
 int /*<<< orphan*/  LmPRMSTAT0 (int) ; 
 int /*<<< orphan*/  LmPRMSTAT1 (int) ; 
 int /*<<< orphan*/  LmREQMBX (int) ; 
 int /*<<< orphan*/  LmRSPMBX (int) ; 
 scalar_t__ LmSCRATCHPAGE (int) ; 
 scalar_t__ LmWWN (int) ; 
 int RSTINTCTL ; 
 int SAS_ADDR_SIZE ; 
 int SAS_ALIGN_DEFAULT ; 
 int STP_ALIGN_DEFAULT ; 
 int /*<<< orphan*/  asd_read_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_write_reg_byte (struct asd_ha_struct*,scalar_t__,int) ; 
 int /*<<< orphan*/  asd_write_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  asd_write_reg_word (struct asd_ha_struct*,int /*<<< orphan*/ ,int) ; 
 int lseq_idle_loop ; 
 int* lseq_vecs ; 

__attribute__((used)) static void asd_init_lseq_cio(struct asd_ha_struct *asd_ha, int lseq)
{
	u8  *sas_addr;
	int  i;

	/* Enable ARP2HALTC (ARP2 Halted from Halt Code Write). */
	asd_write_reg_dword(asd_ha, LmARP2INTEN(lseq), EN_ARP2HALTC);

	asd_write_reg_byte(asd_ha, LmSCRATCHPAGE(lseq), 0);

	/* Initialize Mode 0,1, and 2 SCRATCHPAGE to 0. */
	for (i = 0; i < 3; i++)
		asd_write_reg_byte(asd_ha, LmMnSCRATCHPAGE(lseq, i), 0);

	/* Initialize Mode 5 SCRATCHPAGE to 0. */
	asd_write_reg_byte(asd_ha, LmMnSCRATCHPAGE(lseq, 5), 0);

	asd_write_reg_dword(asd_ha, LmRSPMBX(lseq), 0);
	/* Initialize Mode 0,1,2 and 5 Interrupt Enable and
	 * Interrupt registers. */
	asd_write_reg_dword(asd_ha, LmMnINTEN(lseq, 0), LmM0INTEN_MASK);
	asd_write_reg_dword(asd_ha, LmMnINT(lseq, 0), 0xFFFFFFFF);
	/* Mode 1 */
	asd_write_reg_dword(asd_ha, LmMnINTEN(lseq, 1), LmM1INTEN_MASK);
	asd_write_reg_dword(asd_ha, LmMnINT(lseq, 1), 0xFFFFFFFF);
	/* Mode 2 */
	asd_write_reg_dword(asd_ha, LmMnINTEN(lseq, 2), LmM2INTEN_MASK);
	asd_write_reg_dword(asd_ha, LmMnINT(lseq, 2), 0xFFFFFFFF);
	/* Mode 5 */
	asd_write_reg_dword(asd_ha, LmMnINTEN(lseq, 5), LmM5INTEN_MASK);
	asd_write_reg_dword(asd_ha, LmMnINT(lseq, 5), 0xFFFFFFFF);

	/* Enable HW Timer status. */
	asd_write_reg_byte(asd_ha, LmHWTSTATEN(lseq), LmHWTSTATEN_MASK);

	/* Enable Primitive Status 0 and 1. */
	asd_write_reg_dword(asd_ha, LmPRIMSTAT0EN(lseq), LmPRIMSTAT0EN_MASK);
	asd_write_reg_dword(asd_ha, LmPRIMSTAT1EN(lseq), LmPRIMSTAT1EN_MASK);

	/* Enable Frame Error. */
	asd_write_reg_dword(asd_ha, LmFRMERREN(lseq), LmFRMERREN_MASK);
	asd_write_reg_byte(asd_ha, LmMnHOLDLVL(lseq, 0), 0x50);

	/* Initialize Mode 0 Transfer Level to 512. */
	asd_write_reg_byte(asd_ha,  LmMnXFRLVL(lseq, 0), LmMnXFRLVL_512);
	/* Initialize Mode 1 Transfer Level to 256. */
	asd_write_reg_byte(asd_ha, LmMnXFRLVL(lseq, 1), LmMnXFRLVL_256);

	/* Initialize Program Count. */
	asd_write_reg_word(asd_ha, LmPRGMCNT(lseq), lseq_idle_loop);

	/* Enable Blind SG Move. */
	asd_write_reg_dword(asd_ha, LmMODECTL(lseq), LmBLIND48);
	asd_write_reg_word(asd_ha, LmM3SATATIMER(lseq),
			   ASD_SATA_INTERLOCK_TIMEOUT);

	(void) asd_read_reg_dword(asd_ha, LmREQMBX(lseq));

	/* Clear Primitive Status 0 and 1. */
	asd_write_reg_dword(asd_ha, LmPRMSTAT0(lseq), 0xFFFFFFFF);
	asd_write_reg_dword(asd_ha, LmPRMSTAT1(lseq), 0xFFFFFFFF);

	/* Clear HW Timer status. */
	asd_write_reg_byte(asd_ha, LmHWTSTAT(lseq), 0xFF);

	/* Clear DMA Errors for Mode 0 and 1. */
	asd_write_reg_byte(asd_ha, LmMnDMAERRS(lseq, 0), 0xFF);
	asd_write_reg_byte(asd_ha, LmMnDMAERRS(lseq, 1), 0xFF);

	/* Clear SG DMA Errors for Mode 0 and 1. */
	asd_write_reg_byte(asd_ha, LmMnSGDMAERRS(lseq, 0), 0xFF);
	asd_write_reg_byte(asd_ha, LmMnSGDMAERRS(lseq, 1), 0xFF);

	/* Clear Mode 0 Buffer Parity Error. */
	asd_write_reg_byte(asd_ha, LmMnBUFSTAT(lseq, 0), LmMnBUFPERR);

	/* Clear Mode 0 Frame Error register. */
	asd_write_reg_dword(asd_ha, LmMnFRMERR(lseq, 0), 0xFFFFFFFF);

	/* Reset LSEQ external interrupt arbiter. */
	asd_write_reg_byte(asd_ha, LmARP2INTCTL(lseq), RSTINTCTL);

	/* Set the Phy SAS for the LmSEQ WWN. */
	sas_addr = asd_ha->phys[lseq].phy_desc->sas_addr;
	for (i = 0; i < SAS_ADDR_SIZE; i++)
		asd_write_reg_byte(asd_ha, LmWWN(lseq) + i, sas_addr[i]);

	/* Set the Transmit Size to 1024 bytes, 0 = 256 Dwords. */
	asd_write_reg_byte(asd_ha, LmMnXMTSIZE(lseq, 1), 0);

	/* Set the Bus Inactivity Time Limit Timer. */
	asd_write_reg_word(asd_ha, LmBITL_TIMER(lseq), 9);

	/* Enable SATA Port Multiplier. */
	asd_write_reg_byte(asd_ha, LmMnSATAFS(lseq, 1), 0x80);

	/* Initialize Interrupt Vector[0-10] address in Mode 3.
	 * See the comment on CSEQ_INT_* */
	asd_write_reg_word(asd_ha, LmM3INTVEC0(lseq), lseq_vecs[0]);
	asd_write_reg_word(asd_ha, LmM3INTVEC1(lseq), lseq_vecs[1]);
	asd_write_reg_word(asd_ha, LmM3INTVEC2(lseq), lseq_vecs[2]);
	asd_write_reg_word(asd_ha, LmM3INTVEC3(lseq), lseq_vecs[3]);
	asd_write_reg_word(asd_ha, LmM3INTVEC4(lseq), lseq_vecs[4]);
	asd_write_reg_word(asd_ha, LmM3INTVEC5(lseq), lseq_vecs[5]);
	asd_write_reg_word(asd_ha, LmM3INTVEC6(lseq), lseq_vecs[6]);
	asd_write_reg_word(asd_ha, LmM3INTVEC7(lseq), lseq_vecs[7]);
	asd_write_reg_word(asd_ha, LmM3INTVEC8(lseq), lseq_vecs[8]);
	asd_write_reg_word(asd_ha, LmM3INTVEC9(lseq), lseq_vecs[9]);
	asd_write_reg_word(asd_ha, LmM3INTVEC10(lseq), lseq_vecs[10]);
	/*
	 * Program the Link LED control, applicable only for
	 * Chip Rev. B or later.
	 */
	asd_write_reg_dword(asd_ha, LmCONTROL(lseq),
			    (LEDTIMER | LEDMODE_TXRX | LEDTIMERS_100ms));

	/* Set the Align Rate for SAS and STP mode. */
	asd_write_reg_byte(asd_ha, LmM1SASALIGN(lseq), SAS_ALIGN_DEFAULT);
	asd_write_reg_byte(asd_ha, LmM1STPALIGN(lseq), STP_ALIGN_DEFAULT);
}