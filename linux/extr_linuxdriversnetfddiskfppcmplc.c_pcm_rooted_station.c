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
struct TYPE_4__ {TYPE_1__* mib; } ;
struct TYPE_3__ {scalar_t__ fddiPORTPCMState; scalar_t__ fddiPORTNeighborType; } ;

/* Variables and functions */
 int NUMPHYS ; 
 scalar_t__ PC8_ACTIVE ; 
 scalar_t__ TM ; 

int pcm_rooted_station(struct s_smc *smc)
{
	int	n ;

	for (n = 0 ; n < NUMPHYS ; n++) {
		if (smc->y[n].mib->fddiPORTPCMState == PC8_ACTIVE &&
		    smc->y[n].mib->fddiPORTNeighborType == TM)
			return 0;
	}
	return 1;
}