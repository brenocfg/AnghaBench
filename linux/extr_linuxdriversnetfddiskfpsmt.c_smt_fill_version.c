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
struct smt_p_version {int v_n; int v_index; scalar_t__ v_pad2; int /*<<< orphan*/ * v_version; scalar_t__ v_pad; } ;
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SK_UNUSED (struct s_smc*) ; 
 int /*<<< orphan*/  SMTSETPARA (struct smt_p_version*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMT_P_VERSION ; 
 int /*<<< orphan*/  SMT_VID_2 ; 

__attribute__((used)) static void smt_fill_version(struct s_smc *smc, struct smt_p_version *vers)
{
	SK_UNUSED(smc) ;
	SMTSETPARA(vers,SMT_P_VERSION) ;
	vers->v_pad = 0 ;
	vers->v_n = 1 ;				/* one version is enough .. */
	vers->v_index = 1 ;
	vers->v_version[0] = SMT_VID_2 ;
	vers->v_pad2 = 0 ;
}