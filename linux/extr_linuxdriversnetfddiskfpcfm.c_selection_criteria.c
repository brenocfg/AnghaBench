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
struct s_smc {TYPE_2__* y; } ;
struct s_phy {void* wc_flag; TYPE_1__* mib; } ;
struct TYPE_4__ {int /*<<< orphan*/  cf_join; } ;
struct TYPE_3__ {int fddiPORTMy_Type; } ;

/* Variables and functions */
 void* FALSE ; 
 size_t PB ; 
#define  TA 131 
#define  TB 130 
 int /*<<< orphan*/  THRU_ENABLED (struct s_smc*) ; 
#define  TM 129 
 void* TRUE ; 
#define  TS 128 

__attribute__((used)) static void selection_criteria (struct s_smc *smc, struct s_phy *phy)
{

	switch (phy->mib->fddiPORTMy_Type) {
	case TA:
		if ( !THRU_ENABLED(smc) && smc->y[PB].cf_join ) {
			phy->wc_flag = TRUE ;
		} else {
			phy->wc_flag = FALSE ;
		}

		break;
	case TB:
		/* take precedence over PA */
		phy->wc_flag = FALSE ;
		break;
	case TS:
		phy->wc_flag = FALSE ;
		break;
	case TM:
		phy->wc_flag = FALSE ;
		break;
	}

}