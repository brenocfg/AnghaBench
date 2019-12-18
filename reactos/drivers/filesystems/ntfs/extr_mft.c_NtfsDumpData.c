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
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/ * PUCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,...) ; 

void
NtfsDumpData(ULONG_PTR Buffer, ULONG Length)
{
    ULONG i, j;

    // dump binary data, 8 bytes at a time
    for (i = 0; i < Length; i += 8)
    {
        // display current offset, in hex
        DbgPrint("\t%03x\t", i);

        // display hex value of each of the next 8 bytes
        for (j = 0; j < 8; j++)
            DbgPrint("%02x ", *(PUCHAR)(Buffer + i + j));
        DbgPrint("\n");
    }
}