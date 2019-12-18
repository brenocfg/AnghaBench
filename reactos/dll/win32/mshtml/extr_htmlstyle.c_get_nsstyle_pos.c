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
typedef  int /*<<< orphan*/  styleid_t ;
typedef  int /*<<< orphan*/  nsAString ;
typedef  scalar_t__ WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  nsstyle; } ;
typedef  int /*<<< orphan*/  PRUnichar ;
typedef  TYPE_1__ HTMLStyle ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ get_nsstyle_attr_nsval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsAString_GetData (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  nsAString_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pxW ; 
 scalar_t__ strcmpW (scalar_t__*,int /*<<< orphan*/ ) ; 
 float strtolW (int /*<<< orphan*/  const*,scalar_t__**,int) ; 

__attribute__((used)) static HRESULT get_nsstyle_pos(HTMLStyle *This, styleid_t sid, float *p)
{
    nsAString str_value;
    HRESULT hres;

    TRACE("%p %d %p\n", This, sid, p);

    *p = 0.0f;

    nsAString_Init(&str_value, NULL);

    hres = get_nsstyle_attr_nsval(This->nsstyle, sid, &str_value);
    if(hres == S_OK)
    {
        WCHAR *ptr;
        const PRUnichar *value;

        nsAString_GetData(&str_value, &value);
        if(value)
        {
            *p = strtolW(value, &ptr, 10);

            if(*ptr && strcmpW(ptr, pxW))
            {
                nsAString_Finish(&str_value);
                FIXME("only px values are currently supported\n");
                hres = E_FAIL;
            }
        }
    }

    TRACE("ret %f\n", *p);

    nsAString_Finish(&str_value);
    return hres;
}