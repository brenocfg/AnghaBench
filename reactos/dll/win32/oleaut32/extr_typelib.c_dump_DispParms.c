#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int cArgs; unsigned int cNamedArgs; scalar_t__ rgvarg; int /*<<< orphan*/ * rgdispidNamedArgs; } ;
typedef  TYPE_1__ DISPPARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,...) ; 
 unsigned int debugstr_variant (scalar_t__) ; 

__attribute__((used)) static void dump_DispParms(const DISPPARAMS * pdp)
{
    unsigned int index;

    TRACE("args=%u named args=%u\n", pdp->cArgs, pdp->cNamedArgs);

    if (pdp->cNamedArgs && pdp->rgdispidNamedArgs)
    {
        TRACE("named args:\n");
        for (index = 0; index < pdp->cNamedArgs; index++)
            TRACE( "\t0x%x\n", pdp->rgdispidNamedArgs[index] );
    }

    if (pdp->cArgs && pdp->rgvarg)
    {
        TRACE("args:\n");
        for (index = 0; index < pdp->cArgs; index++)
            TRACE("  [%d] %s\n", index, debugstr_variant(pdp->rgvarg+index));
    }
}