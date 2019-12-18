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
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t UINT ;
struct TYPE_4__ {scalar_t__ Handle; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PAFD_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObDereferenceObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_AFD_POLL_HANDLE ; 

VOID UnlockHandles( PAFD_HANDLE HandleArray, UINT HandleCount ) {
    UINT i;

    for( i = 0; i < HandleCount; i++ ) {
        if( HandleArray[i].Handle )
            ObDereferenceObject( (PVOID)HandleArray[i].Handle );
    }

    ExFreePoolWithTag(HandleArray, TAG_AFD_POLL_HANDLE);
    HandleArray = NULL;
}