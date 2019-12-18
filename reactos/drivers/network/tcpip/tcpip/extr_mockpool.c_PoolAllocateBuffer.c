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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PVOID ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MEMORY ; 
 int /*<<< orphan*/  TI_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 

PVOID PoolAllocateBuffer(
    ULONG Size)
/*
 * FUNCTION: Returns a buffer from the free buffer pool
 * RETURNS:
 *     Pointer to buffer, NULL if there was not enough
 *     free resources
 */
{
    PVOID Buffer;

    /* FIXME: Get buffer from a free buffer pool with enough room */

    Buffer = malloc(Size);

    TI_DbgPrint(DEBUG_MEMORY, ("Allocated (%i) bytes at (0x%X).\n", Size, Buffer));

    return Buffer;
}