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
typedef  scalar_t__ u_char ;
struct TYPE_2__ {int uniq_ticks; int uniq_time; } ;
struct s_smc {TYPE_1__ sm; } ;

/* Variables and functions */
 int TICKS_PER_SECOND ; 
 int smt_get_time () ; 

void smt_set_timestamp(struct s_smc *smc, u_char *p)
{
	u_long	time ;
	u_long	utime ;

	/*
	 * timestamp is 64 bits long ; resolution is 80 nS
	 * our clock resolution is 10mS
	 * 10mS/80ns = 125000 ~ 2^17 = 131072
	 */
	utime = smt_get_time() ;
	time = utime * 100 ;
	time /= TICKS_PER_SECOND ;
	p[0] = 0 ;
	p[1] = (u_char)((time>>(8+8+8+8-1)) & 1) ;
	p[2] = (u_char)(time>>(8+8+8-1)) ;
	p[3] = (u_char)(time>>(8+8-1)) ;
	p[4] = (u_char)(time>>(8-1)) ;
	p[5] = (u_char)(time<<1) ;
	p[6] = (u_char)(smc->sm.uniq_ticks>>8) ;
	p[7] = (u_char)smc->sm.uniq_ticks ;
	/*
	 * make sure we don't wrap: restart whenever the upper digits change
	 */
	if (utime != smc->sm.uniq_time) {
		smc->sm.uniq_ticks = 0 ;
	}
	smc->sm.uniq_ticks++ ;
	smc->sm.uniq_time = utime ;
}