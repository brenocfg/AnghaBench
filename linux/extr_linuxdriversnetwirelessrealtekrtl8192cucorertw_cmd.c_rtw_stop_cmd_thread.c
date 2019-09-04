#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cmdthd_running; int stop_req; int /*<<< orphan*/  terminate_cmdthread_sema; int /*<<< orphan*/  cmd_queue_sema; } ;
struct TYPE_5__ {TYPE_1__ cmdpriv; scalar_t__ cmdThread; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _rtw_down_sema (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_up_sema (int /*<<< orphan*/ *) ; 

void rtw_stop_cmd_thread(_adapter *adapter)
{
	if(adapter->cmdThread && adapter->cmdpriv.cmdthd_running == _TRUE
		&& adapter->cmdpriv.stop_req == 0)
	{
		adapter->cmdpriv.stop_req = 1;
		_rtw_up_sema(&adapter->cmdpriv.cmd_queue_sema);
		_rtw_down_sema(&adapter->cmdpriv.terminate_cmdthread_sema);
	}
}