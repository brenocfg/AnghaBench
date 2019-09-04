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
struct TYPE_2__ {scalar_t__ scbpro; } ;
struct asd_ha_struct {TYPE_1__ seq; } ;

/* Variables and functions */
 int ASD_DL_SIZE_BITS ; 
 scalar_t__ CARP2INTEN ; 
 int /*<<< orphan*/  CM11INTVEC0 ; 
 int /*<<< orphan*/  CM11INTVEC1 ; 
 int /*<<< orphan*/  CM11INTVEC2 ; 
 int /*<<< orphan*/  CMnINTEN (int) ; 
 int /*<<< orphan*/  CMnREQMBX (int) ; 
 scalar_t__ CMnSCRATCHPAGE (int) ; 
 int /*<<< orphan*/  CPRGMCNT ; 
 scalar_t__ CSCRATCHPAGE ; 
 scalar_t__ CSEQCOMINTEN ; 
 int /*<<< orphan*/  CSEQCON ; 
 scalar_t__ CSEQDLCTL ; 
 scalar_t__ CSEQDLOFFS ; 
 int EN_ARP2HALTC ; 
 int /*<<< orphan*/  EN_CMnRSPMBXF ; 
 int /*<<< orphan*/  SCBPRO ; 
 int /*<<< orphan*/  asd_write_reg_byte (struct asd_ha_struct*,scalar_t__,int) ; 
 int /*<<< orphan*/  asd_write_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_write_reg_word (struct asd_ha_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cseq_idle_loop ; 
 int /*<<< orphan*/ * cseq_vecs ; 

__attribute__((used)) static void asd_init_cseq_cio(struct asd_ha_struct *asd_ha)
{
	int i;

	asd_write_reg_byte(asd_ha, CSEQCOMINTEN, 0);
	asd_write_reg_byte(asd_ha, CSEQDLCTL, ASD_DL_SIZE_BITS);
	asd_write_reg_byte(asd_ha, CSEQDLOFFS, 0);
	asd_write_reg_byte(asd_ha, CSEQDLOFFS+1, 0);
	asd_ha->seq.scbpro = 0;
	asd_write_reg_dword(asd_ha, SCBPRO, 0);
	asd_write_reg_dword(asd_ha, CSEQCON, 0);

	/* Initialize CSEQ Mode 11 Interrupt Vectors.
	 * The addresses are 16 bit wide and in dword units.
	 * The values of their macros are in byte units.
	 * Thus we have to divide by 4. */
	asd_write_reg_word(asd_ha, CM11INTVEC0, cseq_vecs[0]);
	asd_write_reg_word(asd_ha, CM11INTVEC1, cseq_vecs[1]);
	asd_write_reg_word(asd_ha, CM11INTVEC2, cseq_vecs[2]);

	/* Enable ARP2HALTC (ARP2 Halted from Halt Code Write). */
	asd_write_reg_byte(asd_ha, CARP2INTEN, EN_ARP2HALTC);

	/* Initialize CSEQ Scratch Page to 0x04. */
	asd_write_reg_byte(asd_ha, CSCRATCHPAGE, 0x04);

	/* Initialize CSEQ Mode[0-8] Dependent registers. */
	/* Initialize Scratch Page to 0. */
	for (i = 0; i < 9; i++)
		asd_write_reg_byte(asd_ha, CMnSCRATCHPAGE(i), 0);

	/* Reset the ARP2 Program Count. */
	asd_write_reg_word(asd_ha, CPRGMCNT, cseq_idle_loop);

	for (i = 0; i < 8; i++) {
		/* Initialize Mode n Link m Interrupt Enable. */
		asd_write_reg_dword(asd_ha, CMnINTEN(i), EN_CMnRSPMBXF);
		/* Initialize Mode n Request Mailbox. */
		asd_write_reg_dword(asd_ha, CMnREQMBX(i), 0);
	}
}