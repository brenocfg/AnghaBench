#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  p_object; } ;
struct TYPE_5__ {scalar_t__ p_type; TYPE_1__ p_vu; } ;
typedef  TYPE_2__ AMFObjectProperty ;
typedef  int /*<<< orphan*/  AMFObject ;

/* Variables and functions */
 int /*<<< orphan*/  AMFObj_Invalid ; 
 scalar_t__ AMF_OBJECT ; 

void
AMFProp_GetObject(AMFObjectProperty *prop, AMFObject *obj)
{
    if (prop->p_type == AMF_OBJECT)
        *obj = prop->p_vu.p_object;
    else
        *obj = AMFObj_Invalid;
}