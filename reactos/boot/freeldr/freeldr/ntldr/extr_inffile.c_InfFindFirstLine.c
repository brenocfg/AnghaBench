#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* FirstSection; } ;
struct TYPE_7__ {struct TYPE_7__* Next; int /*<<< orphan*/ * FirstLine; int /*<<< orphan*/  Name; } ;
struct TYPE_6__ {void* Line; void* Section; void* Inf; } ;
typedef  void* PVOID ;
typedef  TYPE_1__* PINFCONTEXT ;
typedef  TYPE_2__* PINFCACHESECTION ;
typedef  int /*<<< orphan*/ * PINFCACHELINE ;
typedef  TYPE_3__* PINFCACHE ;
typedef  int /*<<< orphan*/ * PCSTR ;
typedef  int /*<<< orphan*/ * HINF ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * InfpCacheFindKeyLine (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _stricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

BOOLEAN
InfFindFirstLine (
    HINF InfHandle,
    PCSTR Section,
    PCSTR Key,
    PINFCONTEXT Context)
{
    PINFCACHE Cache;
    PINFCACHESECTION CacheSection;
    PINFCACHELINE CacheLine;

    if ((InfHandle == NULL) || (Section == NULL) || (Context == NULL))
    {
//      DPRINT("Invalid parameter\n");
        return FALSE;
    }

    Cache = (PINFCACHE)InfHandle;

    /* Iterate through list of sections */
    CacheSection = Cache->FirstSection;
    while (CacheSection != NULL)
    {
//      DPRINT("Comparing '%s' and '%s'\n", CacheSection->Name, Section);

        /* Are the section names the same? */
        if (_stricmp(CacheSection->Name, Section) == 0)
        {
            if (Key != NULL)
            {
                CacheLine = InfpCacheFindKeyLine(CacheSection, Key);
            }
            else
            {
                CacheLine = CacheSection->FirstLine;
            }

            if (CacheLine == NULL)
                return FALSE;

            Context->Inf = (PVOID)Cache;
            Context->Section = (PVOID)CacheSection;
            Context->Line = (PVOID)CacheLine;

            return TRUE;
        }

        /* Get the next section */
        CacheSection = CacheSection->Next;
    }

//  DPRINT("Section not found\n");

    return FALSE;
}