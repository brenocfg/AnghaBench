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
typedef  int ULONGLONG ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int* PULONGLONG ;
typedef  int* PULONG ;
typedef  int* PUCHAR ;
typedef  int /*<<< orphan*/  PPDO_DEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int PCI_ADDRESS_IO_ADDRESS_MASK_64 ; 
 int PCI_ADDRESS_IO_SPACE ; 
 int PCI_ADDRESS_MEMORY_ADDRESS_MASK_64 ; 
 int PCI_ADDRESS_MEMORY_TYPE_MASK ; 
 int PCI_TYPE_20BIT ; 
 int PCI_TYPE_32BIT ; 
 int PCI_TYPE_64BIT ; 
 int /*<<< orphan*/  PdoReadPciBar (int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
PdoGetRangeLength(PPDO_DEVICE_EXTENSION DeviceExtension,
                  UCHAR Bar,
                  PULONGLONG Base,
                  PULONGLONG Length,
                  PULONG Flags,
                  PUCHAR NextBar,
                  PULONGLONG MaximumAddress)
{
    union {
        struct {
            ULONG Bar0;
            ULONG Bar1;
        } Bars;
        ULONGLONG Bar;
    } OriginalValue;
    union {
        struct {
            ULONG Bar0;
            ULONG Bar1;
        } Bars;
        ULONGLONG Bar;
    } NewValue;
    ULONG Offset;

    /* Compute the offset of this BAR in PCI config space */
    Offset = 0x10 + Bar * 4;

    /* Assume this is a 32-bit BAR until we find wrong */
    *NextBar = Bar + 1;

    /* Initialize BAR values to zero */
    OriginalValue.Bar = 0ULL;
    NewValue.Bar = 0ULL;

    /* Read the first BAR */
    if (!PdoReadPciBar(DeviceExtension, Offset,
                       &OriginalValue.Bars.Bar0,
                       &NewValue.Bars.Bar0))
    {
        return FALSE;
    }

    /* Check if this is a memory BAR */
    if (!(OriginalValue.Bars.Bar0 & PCI_ADDRESS_IO_SPACE))
    {
        /* Write the maximum address if the caller asked for it */
        if (MaximumAddress != NULL)
        {
            if ((OriginalValue.Bars.Bar0 & PCI_ADDRESS_MEMORY_TYPE_MASK) == PCI_TYPE_32BIT)
            {
                *MaximumAddress = 0x00000000FFFFFFFFULL;
            }
            else if ((OriginalValue.Bars.Bar0 & PCI_ADDRESS_MEMORY_TYPE_MASK) == PCI_TYPE_20BIT)
            {
                *MaximumAddress = 0x00000000000FFFFFULL;
            }
            else if ((OriginalValue.Bars.Bar0 & PCI_ADDRESS_MEMORY_TYPE_MASK) == PCI_TYPE_64BIT)
            {
                *MaximumAddress = 0xFFFFFFFFFFFFFFFFULL;
            }
        }

        /* Check if this is a 64-bit BAR */
        if ((OriginalValue.Bars.Bar0 & PCI_ADDRESS_MEMORY_TYPE_MASK) == PCI_TYPE_64BIT)
        {
            /* We've now consumed the next BAR too */
            *NextBar = Bar + 2;

            /* Read the next BAR */
            if (!PdoReadPciBar(DeviceExtension, Offset + 4,
                               &OriginalValue.Bars.Bar1,
                               &NewValue.Bars.Bar1))
            {
                return FALSE;
            }
        }
    }
    else
    {
        /* Write the maximum I/O port address */
        if (MaximumAddress != NULL)
        {
            *MaximumAddress = 0x00000000FFFFFFFFULL;
        }
    }

    if (NewValue.Bar == 0)
    {
        DPRINT("Unused address register\n");
        *Base = 0;
        *Length = 0;
        *Flags = 0;
        return TRUE;
    }

    *Base = ((OriginalValue.Bar & PCI_ADDRESS_IO_SPACE)
             ? (OriginalValue.Bar & PCI_ADDRESS_IO_ADDRESS_MASK_64)
             : (OriginalValue.Bar & PCI_ADDRESS_MEMORY_ADDRESS_MASK_64));

    *Length = ~((NewValue.Bar & PCI_ADDRESS_IO_SPACE)
                ? (NewValue.Bar & PCI_ADDRESS_IO_ADDRESS_MASK_64)
                : (NewValue.Bar & PCI_ADDRESS_MEMORY_ADDRESS_MASK_64)) + 1;

    *Flags = (NewValue.Bar & PCI_ADDRESS_IO_SPACE)
             ? (NewValue.Bar & ~PCI_ADDRESS_IO_ADDRESS_MASK_64)
             : (NewValue.Bar & ~PCI_ADDRESS_MEMORY_ADDRESS_MASK_64);

    return TRUE;
}