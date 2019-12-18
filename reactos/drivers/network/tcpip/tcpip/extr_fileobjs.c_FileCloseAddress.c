#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ Listener; int /*<<< orphan*/  Sharers; } ;
struct TYPE_8__ {TYPE_3__* AddressHandle; } ;
struct TYPE_9__ {TYPE_1__ Handle; } ;
typedef  TYPE_2__* PTDI_REQUEST ;
typedef  TYPE_3__* PADDRESS_FILE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  DereferenceObject (TYPE_3__*) ; 
 scalar_t__ InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockObject (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TCPClose (scalar_t__) ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UnlockObject (TYPE_3__*,int /*<<< orphan*/ ) ; 

NTSTATUS FileCloseAddress(
  PTDI_REQUEST Request)
{
  PADDRESS_FILE AddrFile = Request->Handle.AddressHandle;
  KIRQL OldIrql;

  if (!Request->Handle.AddressHandle) return STATUS_INVALID_PARAMETER;

  LockObject(AddrFile, &OldIrql);

  if (InterlockedDecrement(&AddrFile->Sharers) != 0)
  {
      /* Still other guys have open handles to this, so keep it around */
      UnlockObject(AddrFile, OldIrql);
      return STATUS_SUCCESS;
  }

  /* We have to close this listener because we started it */
  if( AddrFile->Listener )
  {
      TCPClose( AddrFile->Listener );
  }

  UnlockObject(AddrFile, OldIrql);

  DereferenceObject(AddrFile);

  TI_DbgPrint(MAX_TRACE, ("Leaving.\n"));

  return STATUS_SUCCESS;
}