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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  size_t UINT ;
struct TYPE_3__ {size_t cArgs; size_t cNamedArgs; size_t* rgdispidNamedArgs; int /*<<< orphan*/ * rgvarg; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DISPPARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_PARAMNOTFOUND ; 
 int /*<<< orphan*/  TRACE (char*,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  VariantCopyInd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT DispGetParam_CopyOnly(
        DISPPARAMS *pdispparams, /* [in] Parameter list */
        UINT        *position,    /* [in] Position of parameter to copy in pdispparams; on return will contain calculated position */
        VARIANT    *pvarResult)  /* [out] Destination for resulting variant */
{
    /* position is counted backwards */
    UINT pos;

    TRACE("position=%d, cArgs=%d, cNamedArgs=%d\n",
          *position, pdispparams->cArgs, pdispparams->cNamedArgs);
    if (*position < pdispparams->cArgs) {
      /* positional arg? */
      pos = pdispparams->cArgs - *position - 1;
    } else {
      /* FIXME: is this how to handle named args? */
      for (pos=0; pos<pdispparams->cNamedArgs; pos++)
        if (pdispparams->rgdispidNamedArgs[pos] == *position) break;

      if (pos==pdispparams->cNamedArgs)
        return DISP_E_PARAMNOTFOUND;
    }
    *position = pos;
    return VariantCopyInd(pvarResult,
                        &pdispparams->rgvarg[pos]);
}