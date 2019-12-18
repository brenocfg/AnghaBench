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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  TDI_STATUS ;
typedef  int /*<<< orphan*/  TDIEntityID ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  PUINT ;
typedef  int /*<<< orphan*/ * PNDIS_BUFFER ;
typedef  int /*<<< orphan*/  PIP_INTERFACE ;
typedef  int /*<<< orphan*/ * PIPARP_ENTRY ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IPARP_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  ARP_ENTRY_TAG ; 
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfoCopyOut (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NBCopyNeighbors (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 

TDI_STATUS InfoTdiQueryGetArptableMIB(TDIEntityID ID,
				      PIP_INTERFACE Interface,
				      PNDIS_BUFFER Buffer,
				      PUINT BufferSize) {
    NTSTATUS Status;
    ULONG NumNeighbors = NBCopyNeighbors( Interface, NULL );
    ULONG MemSize = NumNeighbors * sizeof(IPARP_ENTRY);
    PIPARP_ENTRY ArpEntries;

    if (MemSize != 0)
    {
        ArpEntries = ExAllocatePoolWithTag( NonPagedPool, MemSize, ARP_ENTRY_TAG );
        if( !ArpEntries ) return STATUS_NO_MEMORY;

        NBCopyNeighbors( Interface, ArpEntries );

        Status = InfoCopyOut( (PVOID)ArpEntries, MemSize, Buffer, BufferSize );

        ExFreePoolWithTag( ArpEntries, ARP_ENTRY_TAG );
    }
    else
    {
        Status = InfoCopyOut(NULL, 0, NULL, BufferSize);
    }

    return Status;
}