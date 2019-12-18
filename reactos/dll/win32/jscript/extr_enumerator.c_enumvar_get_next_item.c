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
struct TYPE_3__ {scalar_t__ atend; void* item; int /*<<< orphan*/  enumvar; } ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ EnumeratorInstance ;

/* Variables and functions */
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IEnumVARIANT_Next (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  jsval_release (void*) ; 
 void* jsval_undefined () ; 
 scalar_t__ variant_to_jsval (int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static inline HRESULT enumvar_get_next_item(EnumeratorInstance *This)
{
    HRESULT hres;
    VARIANT nextitem;

    if (This->atend)
        return S_OK;

    /* don't leak previous value */
    jsval_release(This->item);

    /* not at end ... get next item */
    VariantInit(&nextitem);
    hres = IEnumVARIANT_Next(This->enumvar, 1, &nextitem, NULL);
    if (hres == S_OK)
    {
        hres = variant_to_jsval(&nextitem, &This->item);
        VariantClear(&nextitem);
        if (FAILED(hres))
        {
            WARN("failed to convert jsval to variant!\n");
            This->item = jsval_undefined();
            return hres;
        }
    }
    else
    {
        This->item = jsval_undefined();
        This->atend = TRUE;
    }

    return S_OK;
}