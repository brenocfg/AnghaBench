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
struct TYPE_6__ {struct TYPE_6__* Prev; struct TYPE_6__* Next; int /*<<< orphan*/  Data; } ;
struct TYPE_5__ {int /*<<< orphan*/  FieldCount; TYPE_2__* LastField; TYPE_2__* FirstField; } ;
typedef  scalar_t__ SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__* PINFCACHELINE ;
typedef  TYPE_2__* PINFCACHEFIELD ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  INFCACHEFIELD ;

/* Variables and functions */
 scalar_t__ FrLdrTempAlloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_INF_FIELD ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
PVOID
InfpAddFieldToLine(
    PINFCACHELINE Line,
    PCHAR Data)
{
    PINFCACHEFIELD Field;
    SIZE_T Size;

    Size = sizeof(INFCACHEFIELD) + strlen(Data);
    Field = (PINFCACHEFIELD)FrLdrTempAlloc(Size, TAG_INF_FIELD);
    if (Field == NULL)
    {
        return NULL;
    }
    memset(Field, 0, Size);

    strcpy(Field->Data, Data);

    /* Append key */
    if (Line->FirstField == NULL)
    {
        Line->FirstField = Field;
        Line->LastField = Field;
    }
    else
    {
        Line->LastField->Next = Field;
        Field->Prev = Line->LastField;
        Line->LastField = Field;
    }
    Line->FieldCount++;

    return (PVOID)Field;
}