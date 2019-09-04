#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * av_val; scalar_t__ av_len; } ;
struct TYPE_6__ {TYPE_1__ p_aval; int /*<<< orphan*/  p_object; } ;
struct TYPE_7__ {scalar_t__ p_type; TYPE_2__ p_vu; } ;
typedef  TYPE_3__ AMFObjectProperty ;

/* Variables and functions */
 scalar_t__ AMF_ECMA_ARRAY ; 
 scalar_t__ AMF_INVALID ; 
 scalar_t__ AMF_OBJECT ; 
 int /*<<< orphan*/  AMF_Reset (int /*<<< orphan*/ *) ; 
 scalar_t__ AMF_STRICT_ARRAY ; 

void
AMFProp_Reset(AMFObjectProperty *prop)
{
    if (prop->p_type == AMF_OBJECT || prop->p_type == AMF_ECMA_ARRAY || prop->p_type == AMF_STRICT_ARRAY)
        AMF_Reset(&prop->p_vu.p_object);
    else
    {
        prop->p_vu.p_aval.av_len = 0;
        prop->p_vu.p_aval.av_val = NULL;
    }
    prop->p_type = AMF_INVALID;
}