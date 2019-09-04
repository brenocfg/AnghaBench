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
struct seq_file {struct fsl_ssi_dbg* private; } ;
struct fsl_ssi_dbg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDAU_EN ; 
 int /*<<< orphan*/  CMDDU_EN ; 
 int /*<<< orphan*/  RDR0_EN ; 
 int /*<<< orphan*/  RDR1_EN ; 
 int /*<<< orphan*/  RFF0_EN ; 
 int /*<<< orphan*/  RFF1_EN ; 
 int /*<<< orphan*/  RFRC_EN ; 
 int /*<<< orphan*/  RFS_EN ; 
 int /*<<< orphan*/  RLS_EN ; 
 int /*<<< orphan*/  ROE0_EN ; 
 int /*<<< orphan*/  ROE1_EN ; 
 int /*<<< orphan*/  RXT_EN ; 
 int /*<<< orphan*/  SIER_SHOW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDE0_EN ; 
 int /*<<< orphan*/  TDE1_EN ; 
 int /*<<< orphan*/  TFE0_EN ; 
 int /*<<< orphan*/  TFE1_EN ; 
 int /*<<< orphan*/  TFRC_EN ; 
 int /*<<< orphan*/  TFS_EN ; 
 int /*<<< orphan*/  TLS_EN ; 
 int /*<<< orphan*/  TUE0_EN ; 
 int /*<<< orphan*/  TUE1_EN ; 
 int /*<<< orphan*/  cmdau ; 
 int /*<<< orphan*/  cmddu ; 
 int /*<<< orphan*/  rdr0 ; 
 int /*<<< orphan*/  rdr1 ; 
 int /*<<< orphan*/  rff0 ; 
 int /*<<< orphan*/  rff1 ; 
 int /*<<< orphan*/  rfrc ; 
 int /*<<< orphan*/  rfs ; 
 int /*<<< orphan*/  rls ; 
 int /*<<< orphan*/  roe0 ; 
 int /*<<< orphan*/  roe1 ; 
 int /*<<< orphan*/  rxt ; 
 int /*<<< orphan*/  tde0 ; 
 int /*<<< orphan*/  tde1 ; 
 int /*<<< orphan*/  tfe0 ; 
 int /*<<< orphan*/  tfe1 ; 
 int /*<<< orphan*/  tfrc ; 
 int /*<<< orphan*/  tfs ; 
 int /*<<< orphan*/  tls ; 
 int /*<<< orphan*/  tue0 ; 
 int /*<<< orphan*/  tue1 ; 

__attribute__((used)) static int fsl_ssi_stats_show(struct seq_file *s, void *unused)
{
	struct fsl_ssi_dbg *ssi_dbg = s->private;

	SIER_SHOW(RFRC_EN, rfrc);
	SIER_SHOW(TFRC_EN, tfrc);
	SIER_SHOW(CMDAU_EN, cmdau);
	SIER_SHOW(CMDDU_EN, cmddu);
	SIER_SHOW(RXT_EN, rxt);
	SIER_SHOW(RDR1_EN, rdr1);
	SIER_SHOW(RDR0_EN, rdr0);
	SIER_SHOW(TDE1_EN, tde1);
	SIER_SHOW(TDE0_EN, tde0);
	SIER_SHOW(ROE1_EN, roe1);
	SIER_SHOW(ROE0_EN, roe0);
	SIER_SHOW(TUE1_EN, tue1);
	SIER_SHOW(TUE0_EN, tue0);
	SIER_SHOW(TFS_EN, tfs);
	SIER_SHOW(RFS_EN, rfs);
	SIER_SHOW(TLS_EN, tls);
	SIER_SHOW(RLS_EN, rls);
	SIER_SHOW(RFF1_EN, rff1);
	SIER_SHOW(RFF0_EN, rff0);
	SIER_SHOW(TFE1_EN, tfe1);
	SIER_SHOW(TFE0_EN, tfe0);

	return 0;
}