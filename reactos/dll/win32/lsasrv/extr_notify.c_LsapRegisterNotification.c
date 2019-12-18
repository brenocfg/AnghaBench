#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  InformationClass; int /*<<< orphan*/  NotificationEventHandle; scalar_t__ Register; } ;
struct TYPE_11__ {TYPE_1__ Request; } ;
struct TYPE_13__ {TYPE_2__ PolicyChangeNotify; } ;
struct TYPE_12__ {int /*<<< orphan*/  Entry; int /*<<< orphan*/  EventHandle; int /*<<< orphan*/  InformationClass; } ;
typedef  TYPE_3__* PLSA_NOTIFICATION_ENTRY ;
typedef  TYPE_4__* PLSA_API_MSG ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LSA_NOTIFICATION_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,TYPE_4__*) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  InsertHeadList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* LsapGetNotificationEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NotificationListHead ; 
 int /*<<< orphan*/  NotificationListLock ; 
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlAcquireResourceExclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  RtlReleaseResource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_INVALID_HANDLE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 

NTSTATUS
LsapRegisterNotification(
    PLSA_API_MSG pRequestMsg)
{
    PLSA_NOTIFICATION_ENTRY pEntry;
    NTSTATUS Status = STATUS_SUCCESS;

    FIXME("LsapRegisterNotification(%p)\n", pRequestMsg);

    /* Acquire the notification list lock exclusively */
    RtlAcquireResourceExclusive(&NotificationListLock, TRUE);

    if (pRequestMsg->PolicyChangeNotify.Request.Register)
    {
        /* Register the notification event */
        pEntry = RtlAllocateHeap(RtlGetProcessHeap(),
                                 HEAP_ZERO_MEMORY,
                                 sizeof(LSA_NOTIFICATION_ENTRY));
        if (pEntry == NULL)
        {
            Status = STATUS_INSUFFICIENT_RESOURCES;
            goto done;
        }

        pEntry->InformationClass = pRequestMsg->PolicyChangeNotify.Request.InformationClass;
        pEntry->EventHandle = pRequestMsg->PolicyChangeNotify.Request.NotificationEventHandle;

        InsertHeadList(&NotificationListHead,
                       &pEntry->Entry);
    }
    else
    {
        /* Unregister the notification event */
        pEntry = LsapGetNotificationEntry(pRequestMsg->PolicyChangeNotify.Request.NotificationEventHandle,
                                          pRequestMsg->PolicyChangeNotify.Request.InformationClass);
        if (pEntry == NULL)
        {
            Status = STATUS_INVALID_HANDLE;
            goto done;
        }

        RemoveEntryList(&pEntry->Entry);
        RtlFreeHeap(RtlGetProcessHeap(), 0, pEntry);
    }

done:
    /* Release the notification list lock */
    RtlReleaseResource(&NotificationListLock);

    return Status;
}