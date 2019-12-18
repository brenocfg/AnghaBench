#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_2__ {int /*<<< orphan*/  SectionItemCount; } ;
typedef  TYPE_1__* PINI_SECTION ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 

ULONG IniGetNumSectionItems(ULONG_PTR SectionId)
{
    PINI_SECTION    Section = (PINI_SECTION)SectionId;

    TRACE("IniGetNumSectionItems() SectionId = 0x%x\n", SectionId);
    TRACE("IniGetNumSectionItems() Item count = %d\n", Section->SectionItemCount);

    return Section->SectionItemCount;
}