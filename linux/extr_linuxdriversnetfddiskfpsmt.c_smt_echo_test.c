#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_6__ {TYPE_2__* m; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pend; } ;
struct s_smc {TYPE_3__ mib; TYPE_1__ sm; } ;
struct TYPE_5__ {int /*<<< orphan*/  fddiMACUpstreamNbr; int /*<<< orphan*/  fddiMACDownstreamNbr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_SMT_INFO ; 
 size_t MAC0 ; 
 int /*<<< orphan*/  SMT_REQUEST ; 
 int SMT_TEST_ECHO_LEN ; 
 size_t SMT_TID_ECF_DNA ; 
 size_t SMT_TID_ECF_UNA ; 
 int /*<<< orphan*/  smt_get_tid (struct s_smc*) ; 
 int /*<<< orphan*/  smt_send_ecf (struct s_smc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void smt_echo_test(struct s_smc *smc, int dna)
{
	u_long	tid ;

	smc->sm.pend[dna ? SMT_TID_ECF_DNA : SMT_TID_ECF_UNA] =
		tid = smt_get_tid(smc) ;
	smt_send_ecf(smc, dna ?
		&smc->mib.m[MAC0].fddiMACDownstreamNbr :
		&smc->mib.m[MAC0].fddiMACUpstreamNbr,
		FC_SMT_INFO,tid, SMT_REQUEST, (SMT_TEST_ECHO_LEN & ~3)-8) ;
}