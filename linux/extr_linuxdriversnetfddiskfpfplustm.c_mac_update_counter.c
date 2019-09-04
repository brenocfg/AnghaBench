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
typedef  void* u_short ;
struct TYPE_4__ {TYPE_1__* m; } ;
struct s_smc {TYPE_2__ mib; } ;
struct TYPE_3__ {int fddiMACFrame_Ct; int fddiMACLost_Ct; int fddiMACError_Ct; int /*<<< orphan*/  fddiMACT_Neg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_ECNTR ; 
 int /*<<< orphan*/  FM_FCNTR ; 
 int /*<<< orphan*/  FM_LCNTR ; 
 size_t MAC0 ; 
 scalar_t__ inpw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_get_tneg (struct s_smc*) ; 
 int /*<<< orphan*/  smt_emulate_token_ct (struct s_smc*,size_t) ; 

void mac_update_counter(struct s_smc *smc)
{
	smc->mib.m[MAC0].fddiMACFrame_Ct =
		(smc->mib.m[MAC0].fddiMACFrame_Ct & 0xffff0000L)
		+ (u_short) inpw(FM_A(FM_FCNTR)) ;
	smc->mib.m[MAC0].fddiMACLost_Ct =
		(smc->mib.m[MAC0].fddiMACLost_Ct & 0xffff0000L)
		+ (u_short) inpw(FM_A(FM_LCNTR)) ;
	smc->mib.m[MAC0].fddiMACError_Ct =
		(smc->mib.m[MAC0].fddiMACError_Ct & 0xffff0000L)
		+ (u_short) inpw(FM_A(FM_ECNTR)) ;
	smc->mib.m[MAC0].fddiMACT_Neg = mac_get_tneg(smc) ;
#ifdef SMT_REAL_TOKEN_CT
	/*
	 * If the token counter is emulated it is updated in smt_event.
	 */
	TBD
#else
	smt_emulate_token_ct( smc, MAC0 );
#endif
}