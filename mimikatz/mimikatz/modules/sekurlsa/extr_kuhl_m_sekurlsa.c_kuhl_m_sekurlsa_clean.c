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
struct TYPE_2__ {int /*<<< orphan*/  (* cleanLocalLib ) () ;} ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 TYPE_1__* lsassLocalHelper ; 
 int /*<<< orphan*/  stub1 () ; 

NTSTATUS kuhl_m_sekurlsa_clean()
{
	NTSTATUS status = STATUS_SUCCESS;
	if(lsassLocalHelper)
	{
		status = lsassLocalHelper->cleanLocalLib();
		lsassLocalHelper = NULL;
	}
	return status;
}