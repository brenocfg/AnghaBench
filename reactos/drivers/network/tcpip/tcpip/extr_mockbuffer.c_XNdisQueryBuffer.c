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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {int /*<<< orphan*/  ByteCount; } ;
struct TYPE_4__ {int /*<<< orphan*/  MappedSystemVa; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/ * PUINT ;
typedef  TYPE_1__* PNDIS_BUFFER ;
typedef  TYPE_2__* PMDL ;

/* Variables and functions */

VOID XNdisQueryBuffer
(PNDIS_BUFFER    Buffer,
 PVOID           *VirtualAddress,
 PUINT           Length)
/*
 * FUNCTION:
 *     Queries an NDIS buffer for information
 * ARGUMENTS:
 *     Buffer         = Pointer to NDIS buffer to query
 *     VirtualAddress = Address of buffer to place virtual address
 *     Length         = Address of buffer to place length of buffer
 */
{
	if (VirtualAddress != NULL)
	    *(PVOID*)VirtualAddress = Buffer->MappedSystemVa;

	*Length = ((PMDL)Buffer)->ByteCount;
}