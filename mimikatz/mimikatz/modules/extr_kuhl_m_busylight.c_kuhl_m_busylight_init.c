#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int id; struct TYPE_5__* next; } ;
typedef  TYPE_1__* PBUSYLIGHT_DEVICE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUSYLIGHT_CAP_LIGHT ; 
 int FALSE ; 
 int /*<<< orphan*/  GetKeyboardLayout (int /*<<< orphan*/ ) ; 
 int PtrToUlong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  isBusyLight ; 
 TYPE_1__* kuhl_m_busylight_devices ; 
 int /*<<< orphan*/  kuhl_m_busylight_steps_KiwiHack ; 
 int /*<<< orphan*/  kuhl_m_busylight_steps_ReneCotyHack ; 
 int /*<<< orphan*/  kull_m_busylight_devices_get (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_busylight_request_send (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

NTSTATUS kuhl_m_busylight_init()
{
	PBUSYLIGHT_DEVICE cur;
	BOOL isKbFR = (PtrToUlong(GetKeyboardLayout(0)) >> 16) == 0x40c, isKiwi = FALSE;
	if(isBusyLight = kull_m_busylight_devices_get(&kuhl_m_busylight_devices, NULL, BUSYLIGHT_CAP_LIGHT, TRUE))
	{
		for(cur = kuhl_m_busylight_devices; cur; cur = cur->next)
		{
			isKiwi = ((!(cur->id % 2) && isKbFR) || ((cur->id % 2) && !isKbFR));
			kull_m_busylight_request_send(cur, isKiwi ? kuhl_m_busylight_steps_KiwiHack : kuhl_m_busylight_steps_ReneCotyHack, isKiwi ? ARRAYSIZE(kuhl_m_busylight_steps_KiwiHack) : ARRAYSIZE(kuhl_m_busylight_steps_ReneCotyHack), FALSE);
		}
	}
	return STATUS_SUCCESS;
}