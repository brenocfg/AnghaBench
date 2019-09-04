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
struct sym_nvram {scalar_t__ type; } ;
struct sym_hcb {int scsi_mode; int features; int sv_stest4; int sv_stest2; int rv_stest2; scalar_t__ sv_scntl3; } ;

/* Variables and functions */
 int FE_DIFF ; 
 int FE_ULTRA2 ; 
 int FE_ULTRA3 ; 
 int INB (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int SMODE ; 
 void* SMODE_HVD ; 
 int SMODE_SE ; 
 int SYM_SETUP_SCSI_DIFF ; 
 scalar_t__ SYM_SYMBIOS_NVRAM ; 
 int /*<<< orphan*/  nc_gpreg ; 

__attribute__((used)) static void sym_set_bus_mode(struct sym_hcb *np, struct sym_nvram *nvram)
{
	if (np->scsi_mode)
		return;

	np->scsi_mode = SMODE_SE;
	if (np->features & (FE_ULTRA2|FE_ULTRA3))
		np->scsi_mode = (np->sv_stest4 & SMODE);
	else if	(np->features & FE_DIFF) {
		if (SYM_SETUP_SCSI_DIFF == 1) {
			if (np->sv_scntl3) {
				if (np->sv_stest2 & 0x20)
					np->scsi_mode = SMODE_HVD;
			} else if (nvram->type == SYM_SYMBIOS_NVRAM) {
				if (!(INB(np, nc_gpreg) & 0x08))
					np->scsi_mode = SMODE_HVD;
			}
		} else if (SYM_SETUP_SCSI_DIFF == 2)
			np->scsi_mode = SMODE_HVD;
	}
	if (np->scsi_mode == SMODE_HVD)
		np->rv_stest2 |= 0x20;
}