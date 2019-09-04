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
struct hw_xmit {scalar_t__ accnt; } ;
typedef  scalar_t__ sint ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 

void rtw_init_hwxmits(struct hw_xmit *phwxmit, sint entry)
{
	sint i;
_func_enter_;	
	for(i = 0; i < entry; i++, phwxmit++)
	{
		//_rtw_spinlock_init(&phwxmit->xmit_lock);
		//_rtw_init_listhead(&phwxmit->pending);		
		//phwxmit->txcmdcnt = 0;
		phwxmit->accnt = 0;
	}
_func_exit_;	
}