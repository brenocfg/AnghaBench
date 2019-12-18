#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* LastSection; TYPE_1__* FirstSection; } ;
struct TYPE_6__ {struct TYPE_6__* Prev; struct TYPE_6__* Next; int /*<<< orphan*/  Name; } ;
typedef  scalar_t__ SIZE_T ;
typedef  TYPE_1__* PINFCACHESECTION ;
typedef  TYPE_2__* PINFCACHE ;
typedef  int /*<<< orphan*/ * PCHAR ;
typedef  int /*<<< orphan*/  INFCACHESECTION ;

/* Variables and functions */
 scalar_t__ FrLdrTempAlloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_INF_SECTION ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
PINFCACHESECTION
InfpCacheAddSection(
    PINFCACHE Cache,
    PCHAR Name)
{
    PINFCACHESECTION Section = NULL;
    SIZE_T Size;

    if ((Cache == NULL) || (Name == NULL))
    {
//      DPRINT("Invalid parameter\n");
        return NULL;
    }

    /* Allocate and initialize the new section */
    Size = sizeof(INFCACHESECTION) + strlen(Name);
    Section = (PINFCACHESECTION)FrLdrTempAlloc(Size, TAG_INF_SECTION);
    if (Section == NULL)
    {
//      DPRINT("RtlAllocateHeap() failed\n");
        return NULL;
    }
    memset(Section, 0, Size);

    /* Copy section name */
    strcpy(Section->Name, Name);

    /* Append section */
    if (Cache->FirstSection == NULL)
    {
        Cache->FirstSection = Section;
        Cache->LastSection = Section;
    }
    else
    {
        Cache->LastSection->Next = Section;
        Section->Prev = Cache->LastSection;
        Cache->LastSection = Section;
    }

    return Section;
}