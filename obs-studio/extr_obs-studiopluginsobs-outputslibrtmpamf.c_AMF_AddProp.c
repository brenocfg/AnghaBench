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
struct TYPE_3__ {int o_num; int /*<<< orphan*/ * o_props; } ;
typedef  int /*<<< orphan*/  AMFObjectProperty ;
typedef  TYPE_1__ AMFObject ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

void
AMF_AddProp(AMFObject *obj, const AMFObjectProperty *prop)
{
    if (!(obj->o_num & 0x0f))
        obj->o_props =
            realloc(obj->o_props, (obj->o_num + 16) * sizeof(AMFObjectProperty));
    memcpy(&obj->o_props[obj->o_num++], prop, sizeof(AMFObjectProperty));
}