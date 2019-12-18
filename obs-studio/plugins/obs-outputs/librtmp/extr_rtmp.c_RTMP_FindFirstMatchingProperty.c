#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int o_num; } ;
struct TYPE_10__ {TYPE_3__ p_object; } ;
struct TYPE_11__ {scalar_t__ p_type; TYPE_1__ p_vu; int /*<<< orphan*/  p_name; } ;
typedef  int /*<<< orphan*/  AVal ;
typedef  TYPE_2__ AMFObjectProperty ;
typedef  TYPE_3__ AMFObject ;

/* Variables and functions */
 scalar_t__ AMF_ECMA_ARRAY ; 
 TYPE_2__* AMF_GetProp (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ AMF_OBJECT ; 
 scalar_t__ AVMATCH (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 

int
RTMP_FindFirstMatchingProperty(AMFObject *obj, const AVal *name,
                               AMFObjectProperty * p)
{
    int n;
    /* this is a small object search to locate the "duration" property */
    for (n = 0; n < obj->o_num; n++)
    {
        AMFObjectProperty *prop = AMF_GetProp(obj, NULL, n);

        if (AVMATCH(&prop->p_name, name))
        {
            memcpy(p, prop, sizeof(*prop));
            return TRUE;
        }

        if (prop->p_type == AMF_OBJECT || prop->p_type == AMF_ECMA_ARRAY)
        {
            if (RTMP_FindFirstMatchingProperty(&prop->p_vu.p_object, name, p))
                return TRUE;
        }
    }
    return FALSE;
}