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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  Set_NETYPE0_MSR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void Set_MSR(_adapter *padapter, u8 type)
{
#ifdef CONFIG_CONCURRENT_MODE
	if(padapter->iface_type == IFACE_PORT1)
	{
		Set_NETYPE1_MSR(padapter, type);
	}
	else
#endif
	{
		Set_NETYPE0_MSR(padapter, type);
	}
}