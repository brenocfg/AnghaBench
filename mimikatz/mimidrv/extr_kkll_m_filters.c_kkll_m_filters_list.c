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
typedef  int ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  DriverName; } ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  TYPE_1__* PDRIVER_OBJECT ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 scalar_t__ ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_1__**,int /*<<< orphan*/ ) ; 
 scalar_t__ IoEnumerateRegisteredFiltersList (TYPE_1__**,int,int*) ; 
 scalar_t__ NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  ObDereferenceObject (TYPE_1__*) ; 
 int /*<<< orphan*/  POOL_TAG ; 
 scalar_t__ STATUS_BUFFER_TOO_SMALL ; 
 scalar_t__ kprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

NTSTATUS kkll_m_filters_list(PKIWI_BUFFER outBuffer)
{
	NTSTATUS status;
	ULONG ActualNumberDriverObjects, sizeOfDriverObjects;
	PDRIVER_OBJECT * DriverObjectList = NULL;
	ULONG i;

	status = IoEnumerateRegisteredFiltersList(NULL, 0, &ActualNumberDriverObjects);
	if((status == STATUS_BUFFER_TOO_SMALL) && ActualNumberDriverObjects)
	{
		sizeOfDriverObjects = sizeof(PDRIVER_OBJECT) * ActualNumberDriverObjects;
		if(DriverObjectList = (PDRIVER_OBJECT *) ExAllocatePoolWithTag(NonPagedPool, sizeOfDriverObjects, POOL_TAG))
		{
			status = IoEnumerateRegisteredFiltersList(DriverObjectList, sizeOfDriverObjects, &ActualNumberDriverObjects);
			for(i = 0; NT_SUCCESS(status) && (i < ActualNumberDriverObjects); i++)
			{
				status = kprintf(outBuffer, L"[%.2u] %wZ\n",i , &(DriverObjectList[i]->DriverName));
				ObDereferenceObject(DriverObjectList[i]);
			}
			ExFreePoolWithTag(DriverObjectList, POOL_TAG);
		}
	}
	return status;
}