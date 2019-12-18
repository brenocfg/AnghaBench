#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Name; int /*<<< orphan*/  MaxNameLen; int /*<<< orphan*/  NameLen; int /*<<< orphan*/  Tag; int /*<<< orphan*/  Scope; int /*<<< orphan*/  Register; int /*<<< orphan*/  Address; int /*<<< orphan*/  Value; int /*<<< orphan*/  Flags; int /*<<< orphan*/  ModBase; int /*<<< orphan*/  Size; int /*<<< orphan*/  Index; int /*<<< orphan*/ * Reserved; int /*<<< orphan*/  TypeIndex; int /*<<< orphan*/  SizeOfStruct; } ;
struct TYPE_5__ {int /*<<< orphan*/  MaxNameLen; int /*<<< orphan*/  Name; int /*<<< orphan*/  NameLen; int /*<<< orphan*/  Tag; int /*<<< orphan*/  Scope; int /*<<< orphan*/  Register; int /*<<< orphan*/  Address; int /*<<< orphan*/  Value; int /*<<< orphan*/  Flags; int /*<<< orphan*/  ModBase; int /*<<< orphan*/  Size; int /*<<< orphan*/  Index; int /*<<< orphan*/ * Reserved; int /*<<< orphan*/  TypeIndex; int /*<<< orphan*/  SizeOfStruct; } ;
typedef  TYPE_1__ SYMBOL_INFOW ;
typedef  TYPE_2__ SYMBOL_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void copy_symbolW(SYMBOL_INFOW* siw, const SYMBOL_INFO* si)
{
    siw->SizeOfStruct = si->SizeOfStruct;
    siw->TypeIndex = si->TypeIndex; 
    siw->Reserved[0] = si->Reserved[0];
    siw->Reserved[1] = si->Reserved[1];
    siw->Index = si->Index;
    siw->Size = si->Size;
    siw->ModBase = si->ModBase;
    siw->Flags = si->Flags;
    siw->Value = si->Value;
    siw->Address = si->Address;
    siw->Register = si->Register;
    siw->Scope = si->Scope;
    siw->Tag = si->Tag;
    siw->NameLen = si->NameLen;
    siw->MaxNameLen = si->MaxNameLen;
    MultiByteToWideChar(CP_ACP, 0, si->Name, -1, siw->Name, siw->MaxNameLen);
}