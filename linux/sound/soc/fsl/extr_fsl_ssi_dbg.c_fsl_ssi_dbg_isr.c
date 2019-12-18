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
struct TYPE_2__ {int /*<<< orphan*/  tfe0; int /*<<< orphan*/  tfe1; int /*<<< orphan*/  rff0; int /*<<< orphan*/  rff1; int /*<<< orphan*/  rls; int /*<<< orphan*/  tls; int /*<<< orphan*/  rfs; int /*<<< orphan*/  tfs; int /*<<< orphan*/  tue0; int /*<<< orphan*/  tue1; int /*<<< orphan*/  roe0; int /*<<< orphan*/  roe1; int /*<<< orphan*/  tde0; int /*<<< orphan*/  tde1; int /*<<< orphan*/  rdr0; int /*<<< orphan*/  rdr1; int /*<<< orphan*/  rxt; int /*<<< orphan*/  cmddu; int /*<<< orphan*/  cmdau; int /*<<< orphan*/  tfrc; int /*<<< orphan*/  rfrc; } ;
struct fsl_ssi_dbg {TYPE_1__ stats; } ;

/* Variables and functions */
 int SSI_SISR_CMDAU ; 
 int SSI_SISR_CMDDU ; 
 int SSI_SISR_RDR0 ; 
 int SSI_SISR_RDR1 ; 
 int SSI_SISR_RFF0 ; 
 int SSI_SISR_RFF1 ; 
 int SSI_SISR_RFRC ; 
 int SSI_SISR_RFS ; 
 int SSI_SISR_RLS ; 
 int SSI_SISR_ROE0 ; 
 int SSI_SISR_ROE1 ; 
 int SSI_SISR_RXT ; 
 int SSI_SISR_TDE0 ; 
 int SSI_SISR_TDE1 ; 
 int SSI_SISR_TFE0 ; 
 int SSI_SISR_TFE1 ; 
 int SSI_SISR_TFRC ; 
 int SSI_SISR_TFS ; 
 int SSI_SISR_TLS ; 
 int SSI_SISR_TUE0 ; 
 int SSI_SISR_TUE1 ; 

void fsl_ssi_dbg_isr(struct fsl_ssi_dbg *dbg, u32 sisr)
{
	if (sisr & SSI_SISR_RFRC)
		dbg->stats.rfrc++;

	if (sisr & SSI_SISR_TFRC)
		dbg->stats.tfrc++;

	if (sisr & SSI_SISR_CMDAU)
		dbg->stats.cmdau++;

	if (sisr & SSI_SISR_CMDDU)
		dbg->stats.cmddu++;

	if (sisr & SSI_SISR_RXT)
		dbg->stats.rxt++;

	if (sisr & SSI_SISR_RDR1)
		dbg->stats.rdr1++;

	if (sisr & SSI_SISR_RDR0)
		dbg->stats.rdr0++;

	if (sisr & SSI_SISR_TDE1)
		dbg->stats.tde1++;

	if (sisr & SSI_SISR_TDE0)
		dbg->stats.tde0++;

	if (sisr & SSI_SISR_ROE1)
		dbg->stats.roe1++;

	if (sisr & SSI_SISR_ROE0)
		dbg->stats.roe0++;

	if (sisr & SSI_SISR_TUE1)
		dbg->stats.tue1++;

	if (sisr & SSI_SISR_TUE0)
		dbg->stats.tue0++;

	if (sisr & SSI_SISR_TFS)
		dbg->stats.tfs++;

	if (sisr & SSI_SISR_RFS)
		dbg->stats.rfs++;

	if (sisr & SSI_SISR_TLS)
		dbg->stats.tls++;

	if (sisr & SSI_SISR_RLS)
		dbg->stats.rls++;

	if (sisr & SSI_SISR_RFF1)
		dbg->stats.rff1++;

	if (sisr & SSI_SISR_RFF0)
		dbg->stats.rff0++;

	if (sisr & SSI_SISR_TFE1)
		dbg->stats.tfe1++;

	if (sisr & SSI_SISR_TFE0)
		dbg->stats.tfe0++;
}