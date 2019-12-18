#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  PosFormat; int /*<<< orphan*/  ExtensionOffset; } ;
struct TYPE_4__ {int /*<<< orphan*/  LookupType; int /*<<< orphan*/ * SubTable; } ;
typedef  TYPE_1__ OT_LookupTable ;
typedef  TYPE_2__ GPOS_ExtensionPosFormat1 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 scalar_t__ GET_BE_DWORD (int /*<<< orphan*/ ) ; 
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 
 int GPOS_LOOKUP_POSITION_EXTENSION ; 

__attribute__((used)) static const BYTE *GPOS_get_subtable(const OT_LookupTable *look, int index)
{
    int offset = GET_BE_WORD(look->SubTable[index]);

    if (GET_BE_WORD(look->LookupType) == GPOS_LOOKUP_POSITION_EXTENSION)
    {
        const GPOS_ExtensionPosFormat1 *ext = (const GPOS_ExtensionPosFormat1 *)((const BYTE *)look + offset);
        if (GET_BE_WORD(ext->PosFormat) == 1)
        {
            offset += GET_BE_DWORD(ext->ExtensionOffset);
        }
        else
        {
            FIXME("Unhandled Extension Positioning Format %i\n",GET_BE_WORD(ext->PosFormat));
        }
    }
    return (const BYTE *)look + offset;
}