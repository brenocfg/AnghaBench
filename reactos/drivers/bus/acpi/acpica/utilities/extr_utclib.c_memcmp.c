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
typedef  scalar_t__ ACPI_SIZE ;

/* Variables and functions */
 scalar_t__ ACPI_SIZE_MAX ; 

int
memcmp (
    void                    *VBuffer1,
    void                    *VBuffer2,
    ACPI_SIZE               Count)
{
    char                    *Buffer1 = (char *) VBuffer1;
    char                    *Buffer2 = (char *) VBuffer2;


    for ( ; Count-- && (*Buffer1 == *Buffer2); Buffer1++, Buffer2++)
    {
    }

    return ((Count == ACPI_SIZE_MAX) ? 0 : ((unsigned char) *Buffer1 -
        (unsigned char) *Buffer2));
}