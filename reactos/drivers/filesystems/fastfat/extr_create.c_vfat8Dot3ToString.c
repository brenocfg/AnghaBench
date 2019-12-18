#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int USHORT ;
struct TYPE_14__ {int* Buffer; int Length; size_t MaximumLength; } ;
struct TYPE_13__ {int /*<<< orphan*/  lCase; int /*<<< orphan*/  ShortName; } ;
struct TYPE_12__ {int Length; int* Buffer; int MaximumLength; } ;
typedef  TYPE_1__* PUNICODE_STRING ;
typedef  TYPE_2__* PFAT_DIR_ENTRY ;
typedef  TYPE_3__ OEM_STRING ;
typedef  int CHAR ;

/* Variables and functions */
 scalar_t__ BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FAT_ENTRY_VOLUME (TYPE_2__*) ; 
 int /*<<< orphan*/  RtlCopyMemory (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlDowncaseUnicodeString (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlOemStringToUnicodeString (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFAT_CASE_LOWER_BASE ; 
 int /*<<< orphan*/  VFAT_CASE_LOWER_EXT ; 

VOID
vfat8Dot3ToString(
    PFAT_DIR_ENTRY pEntry,
    PUNICODE_STRING NameU)
{
    OEM_STRING StringA;
    USHORT Length;
    CHAR  cString[12];

    RtlCopyMemory(cString, pEntry->ShortName, 11);
    cString[11] = 0;
    if (cString[0] == 0x05)
    {
        cString[0] = 0xe5;
    }

    StringA.Buffer = cString;
    for (StringA.Length = 0;
         StringA.Length < 8 && StringA.Buffer[StringA.Length] != ' ';
         StringA.Length++);
    StringA.MaximumLength = StringA.Length;

    RtlOemStringToUnicodeString(NameU, &StringA, FALSE);

    if (BooleanFlagOn(pEntry->lCase, VFAT_CASE_LOWER_BASE))
    {
        RtlDowncaseUnicodeString(NameU, NameU, FALSE);
    }

    if (cString[8] != ' ')
    {
        Length = NameU->Length;
        NameU->Buffer += Length / sizeof(WCHAR);
        if (!FAT_ENTRY_VOLUME(pEntry))
        {
            Length += sizeof(WCHAR);
            NameU->Buffer[0] = L'.';
            NameU->Buffer++;
        }
        NameU->Length = 0;
        NameU->MaximumLength -= Length;

        StringA.Buffer = &cString[8];
        for (StringA.Length = 0;
        StringA.Length < 3 && StringA.Buffer[StringA.Length] != ' ';
        StringA.Length++);
        StringA.MaximumLength = StringA.Length;
        RtlOemStringToUnicodeString(NameU, &StringA, FALSE);
        if (BooleanFlagOn(pEntry->lCase, VFAT_CASE_LOWER_EXT))
        {
            RtlDowncaseUnicodeString(NameU, NameU, FALSE);
        }
        NameU->Buffer -= Length / sizeof(WCHAR);
        NameU->Length += Length;
        NameU->MaximumLength += Length;
    }

    NameU->Buffer[NameU->Length / sizeof(WCHAR)] = 0;
    DPRINT("'%wZ'\n", NameU);
}