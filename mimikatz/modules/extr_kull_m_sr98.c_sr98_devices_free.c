#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; scalar_t__ DevicePath; int /*<<< orphan*/ * hDevice; } ;
typedef  TYPE_1__* PSR98_DEVICE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (TYPE_1__*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 

void sr98_devices_free(PSR98_DEVICE devices)
{
	PSR98_DEVICE tmp;
	while(devices)
	{
		if(devices->hDevice)
		{
			CloseHandle(devices->hDevice);
			devices->hDevice = NULL;
		}
		if(devices->DevicePath)
			free(devices->DevicePath);
		tmp = devices->next;
		LocalFree(devices);
		devices = tmp;
	}
}