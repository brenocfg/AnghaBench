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
struct TYPE_4__ {int VirtualAddress; int SizeOfRawData; } ;
typedef  TYPE_1__ IMAGE_SECTION_HEADER ;
typedef  int DWORD ;

/* Variables and functions */
 TYPE_1__* get_section_header (void*,int,int*) ; 

__attribute__((used)) static const IMAGE_SECTION_HEADER *section_from_rva( void *base, DWORD mapping_size, DWORD rva )
{
    const IMAGE_SECTION_HEADER *sec;
    DWORD num_sections = 0;
    int i;

    sec = get_section_header( base, mapping_size, &num_sections );
    if (!sec)
        return NULL;

    for (i=num_sections-1; i>=0; i--)
    {
        if (sec[i].VirtualAddress <= rva &&
            rva <= (DWORD)sec[i].VirtualAddress + sec[i].SizeOfRawData)
        {
            return &sec[i];
        }
    }

    return NULL;
}