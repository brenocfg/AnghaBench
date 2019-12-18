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
struct TYPE_2__ {int (* map_dwarf_register ) (int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int Wine_DW_no_register ; 
 TYPE_1__* dbghelp_current_cpu ; 
 int stub1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned dwarf2_map_register(int regno)
{
    if (regno == Wine_DW_no_register)
    {
        FIXME("What the heck map reg 0x%x\n",regno);
        return 0;
    }
    return dbghelp_current_cpu->map_dwarf_register(regno, FALSE);
}