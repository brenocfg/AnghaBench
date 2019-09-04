#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * LastField; struct TYPE_6__* FirstField; struct TYPE_6__* Next; struct TYPE_6__* Key; } ;
typedef  TYPE_1__* PINFCACHELINE ;
typedef  TYPE_1__* PINFCACHEFIELD ;

/* Variables and functions */
 int /*<<< orphan*/  FrLdrTempFree (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_INF_FIELD ; 
 int /*<<< orphan*/  TAG_INF_KEY ; 
 int /*<<< orphan*/  TAG_INF_LINE ; 

__attribute__((used)) static
PINFCACHELINE
InfpCacheFreeLine(
    PINFCACHELINE Line)
{
    PINFCACHELINE Next;
    PINFCACHEFIELD Field;

    if (Line == NULL)
    {
        return NULL;
    }

    Next = Line->Next;
    if (Line->Key != NULL)
    {
        FrLdrTempFree(Line->Key, TAG_INF_KEY);
        Line->Key = NULL;
    }

    /* Remove data fields */
    while (Line->FirstField != NULL)
    {
        Field = Line->FirstField->Next;
        FrLdrTempFree(Line->FirstField, TAG_INF_FIELD);
        Line->FirstField = Field;
    }
    Line->LastField = NULL;

    FrLdrTempFree(Line, TAG_INF_LINE);

    return Next;
}