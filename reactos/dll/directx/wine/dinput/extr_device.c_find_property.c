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
struct TYPE_7__ {int /*<<< orphan*/  wine_df; } ;
struct TYPE_6__ {int dwHow; int /*<<< orphan*/  dwObj; } ;
typedef  TYPE_1__* LPCDIPROPHEADER ;
typedef  TYPE_2__ DataFormat ;

/* Variables and functions */
#define  DIPH_BYID 129 
#define  DIPH_BYOFFSET 128 
 int /*<<< orphan*/  FIXME (char*,unsigned int) ; 
 int id_to_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int offset_to_object (TYPE_2__ const*,int /*<<< orphan*/ ) ; 

int find_property(const DataFormat *df, LPCDIPROPHEADER ph)
{
    switch (ph->dwHow)
    {
        case DIPH_BYID:     return id_to_object(df->wine_df, ph->dwObj);
        case DIPH_BYOFFSET: return offset_to_object(df, ph->dwObj);
    }
    FIXME("Unhandled ph->dwHow=='%04X'\n", (unsigned int)ph->dwHow);

    return -1;
}