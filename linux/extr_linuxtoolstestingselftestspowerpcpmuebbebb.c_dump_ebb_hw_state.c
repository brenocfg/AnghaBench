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
typedef  void* u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_BESCR ; 
 int /*<<< orphan*/  SPRN_EBBHR ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 int /*<<< orphan*/  SPRN_MMCR2 ; 
 int /*<<< orphan*/  SPRN_PMC1 ; 
 int /*<<< orphan*/  SPRN_PMC2 ; 
 int /*<<< orphan*/  SPRN_PMC3 ; 
 int /*<<< orphan*/  SPRN_PMC4 ; 
 int /*<<< orphan*/  SPRN_PMC5 ; 
 int /*<<< orphan*/  SPRN_PMC6 ; 
 int /*<<< orphan*/  SPRN_SIAR ; 
 int /*<<< orphan*/  decode_bescr (void*) ; 
 char* decode_mmcr0 (int) ; 
 void* mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,char*,void*,void*,void*,int /*<<< orphan*/ ,void*,void*,void*,void*,void*,void*,void*) ; 

void dump_ebb_hw_state(void)
{
	u64 bescr;
	u32 mmcr0;

	mmcr0 = mfspr(SPRN_MMCR0);
	bescr = mfspr(SPRN_BESCR);

	printf("HW state:\n"		\
	       "MMCR0 0x%016x %s\n"	\
	       "MMCR2 0x%016lx\n"	\
	       "EBBHR 0x%016lx\n"	\
	       "BESCR 0x%016llx %s\n"	\
	       "PMC1  0x%016lx\n"	\
	       "PMC2  0x%016lx\n"	\
	       "PMC3  0x%016lx\n"	\
	       "PMC4  0x%016lx\n"	\
	       "PMC5  0x%016lx\n"	\
	       "PMC6  0x%016lx\n"	\
	       "SIAR  0x%016lx\n",
	       mmcr0, decode_mmcr0(mmcr0), mfspr(SPRN_MMCR2),
	       mfspr(SPRN_EBBHR), bescr, decode_bescr(bescr),
	       mfspr(SPRN_PMC1), mfspr(SPRN_PMC2), mfspr(SPRN_PMC3),
	       mfspr(SPRN_PMC4), mfspr(SPRN_PMC5), mfspr(SPRN_PMC6),
	       mfspr(SPRN_SIAR));
}