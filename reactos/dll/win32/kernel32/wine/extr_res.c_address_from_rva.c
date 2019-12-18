#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ VirtualAddress; scalar_t__ SizeOfRawData; scalar_t__ PointerToRawData; } ;
typedef  scalar_t__ LPBYTE ;
typedef  TYPE_1__ IMAGE_SECTION_HEADER ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 TYPE_1__* section_from_rva (void*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void *address_from_rva( void *base, DWORD mapping_size, DWORD rva, DWORD len )
{
    const IMAGE_SECTION_HEADER *sec;

    sec = section_from_rva( base, mapping_size, rva );
    if (!sec)
        return NULL;

    if (rva + len <= (DWORD)sec->VirtualAddress + sec->SizeOfRawData)
        return (void*)((LPBYTE) base + (sec->PointerToRawData + rva - sec->VirtualAddress));

    return NULL;
}