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
typedef  int u_long ;
struct TYPE_2__ {int smt_tid; } ;
struct s_smc {TYPE_1__ sm; } ;

/* Variables and functions */
 int SMT_TID_MAGIC ; 

u_long smt_get_tid(struct s_smc *smc)
{
	u_long	tid ;
	while ((tid = ++(smc->sm.smt_tid) ^ SMT_TID_MAGIC) == 0)
		;
	return tid & 0x3fffffffL;
}