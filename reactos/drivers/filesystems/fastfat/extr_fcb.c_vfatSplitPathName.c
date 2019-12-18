#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int USHORT ;
struct TYPE_5__ {int* Buffer; int Length; int MaximumLength; } ;
typedef  int* PWCHAR ;
typedef  TYPE_1__* PUNICODE_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

VOID
vfatSplitPathName(
    PUNICODE_STRING PathNameU,
    PUNICODE_STRING DirNameU,
    PUNICODE_STRING FileNameU)
{
    PWCHAR pName;
    USHORT Length = 0;
    pName = PathNameU->Buffer + PathNameU->Length / sizeof(WCHAR) - 1;
    while (*pName != L'\\' && pName >= PathNameU->Buffer)
    {
        pName--;
        Length++;
    }
    ASSERT(*pName == L'\\' || pName < PathNameU->Buffer);
    if (FileNameU)
    {
        FileNameU->Buffer = pName + 1;
        FileNameU->Length = FileNameU->MaximumLength = Length * sizeof(WCHAR);
    }
    if (DirNameU)
    {
        DirNameU->Buffer = PathNameU->Buffer;
        DirNameU->Length = (pName + 1 - PathNameU->Buffer) * sizeof(WCHAR);
        DirNameU->MaximumLength = DirNameU->Length;
    }
}