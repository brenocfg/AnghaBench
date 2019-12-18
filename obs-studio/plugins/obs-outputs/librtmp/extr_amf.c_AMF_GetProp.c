#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int o_num; TYPE_1__* o_props; } ;
struct TYPE_5__ {int /*<<< orphan*/  p_name; } ;
typedef  int /*<<< orphan*/  AVal ;
typedef  TYPE_1__ AMFObjectProperty ;
typedef  TYPE_2__ AMFObject ;

/* Variables and functions */
 int /*<<< orphan*/  AMFProp_Invalid ; 
 scalar_t__ AVMATCH (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

AMFObjectProperty *
AMF_GetProp(AMFObject *obj, const AVal *name, int nIndex)
{
    if (nIndex >= 0)
    {
        if (nIndex < obj->o_num)
            return &obj->o_props[nIndex];
    }
    else
    {
        int n;
        for (n = 0; n < obj->o_num; n++)
        {
            if (AVMATCH(&obj->o_props[n].p_name, name))
                return &obj->o_props[n];
        }
    }

    return (AMFObjectProperty *)&AMFProp_Invalid;
}