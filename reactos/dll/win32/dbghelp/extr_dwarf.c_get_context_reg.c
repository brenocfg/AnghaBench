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
struct TYPE_2__ {unsigned int (* map_dwarf_register ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * (* fetch_context_reg ) (int /*<<< orphan*/ *,unsigned int,unsigned int*) ;} ;
typedef  int /*<<< orphan*/  CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* dbghelp_current_cpu ; 
 unsigned int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ *,unsigned int,unsigned int*) ; 

__attribute__((used)) static ULONG_PTR get_context_reg(CONTEXT *context, ULONG_PTR dw_reg)
{
    unsigned regno = dbghelp_current_cpu->map_dwarf_register(dw_reg, TRUE), sz;
    ULONG_PTR* ptr = dbghelp_current_cpu->fetch_context_reg(context, regno, &sz);

    if (sz != sizeof(ULONG_PTR))
    {
        FIXME("reading register %lu/%u of wrong size %u\n", dw_reg, regno, sz);
        return 0;
    }
    return *ptr;
}