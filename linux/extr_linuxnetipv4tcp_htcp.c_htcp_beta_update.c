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
typedef  int u32 ;
struct htcp {int maxB; int old_maxB; int beta; int modeswitch; } ;

/* Variables and functions */
 void* BETA_MAX ; 
 void* BETA_MIN ; 
 int /*<<< orphan*/  between (int,int,int) ; 
 int msecs_to_jiffies (int) ; 
 scalar_t__ use_bandwidth_switch ; 

__attribute__((used)) static inline void htcp_beta_update(struct htcp *ca, u32 minRTT, u32 maxRTT)
{
	if (use_bandwidth_switch) {
		u32 maxB = ca->maxB;
		u32 old_maxB = ca->old_maxB;

		ca->old_maxB = ca->maxB;
		if (!between(5 * maxB, 4 * old_maxB, 6 * old_maxB)) {
			ca->beta = BETA_MIN;
			ca->modeswitch = 0;
			return;
		}
	}

	if (ca->modeswitch && minRTT > msecs_to_jiffies(10) && maxRTT) {
		ca->beta = (minRTT << 7) / maxRTT;
		if (ca->beta < BETA_MIN)
			ca->beta = BETA_MIN;
		else if (ca->beta > BETA_MAX)
			ca->beta = BETA_MAX;
	} else {
		ca->beta = BETA_MIN;
		ca->modeswitch = 1;
	}
}