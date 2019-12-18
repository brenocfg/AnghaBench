#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_6__ {scalar_t__ Handle; int /*<<< orphan*/  Events; scalar_t__ Status; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PAFD_HANDLE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  AFD_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  AFD_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_ALL_ACCESS ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  ObReferenceObjectByHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TAG_AFD_POLL_HANDLE ; 
 int /*<<< orphan*/  UnlockHandles (TYPE_1__*,int) ; 

PAFD_HANDLE LockHandles( PAFD_HANDLE HandleArray, UINT HandleCount ) {
    UINT i;
    NTSTATUS Status = STATUS_SUCCESS;

    PAFD_HANDLE FileObjects = ExAllocatePoolWithTag(NonPagedPool,
                                                    HandleCount * sizeof(AFD_HANDLE),
                                                    TAG_AFD_POLL_HANDLE);

    for( i = 0; FileObjects && i < HandleCount; i++ ) {
        FileObjects[i].Status = 0;
        FileObjects[i].Events = HandleArray[i].Events;
        FileObjects[i].Handle = 0;
        if( !HandleArray[i].Handle ) continue;
        if( NT_SUCCESS(Status) ) {
                Status = ObReferenceObjectByHandle
                    ( (PVOID)HandleArray[i].Handle,
                      FILE_ALL_ACCESS,
                      NULL,
                       KernelMode,
                       (PVOID*)&FileObjects[i].Handle,
                       NULL );
        }

        if( !NT_SUCCESS(Status) )
        {
            AFD_DbgPrint(MIN_TRACE,("Failed to reference handles (0x%x)\n", Status));
            FileObjects[i].Handle = 0;
        }
    }

    if( !NT_SUCCESS(Status) ) {
        UnlockHandles( FileObjects, HandleCount );
        return NULL;
    }

    return FileObjects;
}