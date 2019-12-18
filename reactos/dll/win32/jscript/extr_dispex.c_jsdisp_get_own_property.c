#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int mask; int flags; int /*<<< orphan*/ * setter; int /*<<< orphan*/ * getter; void* explicit_setter; void* explicit_getter; int /*<<< orphan*/  value; void* explicit_value; } ;
typedef  TYPE_3__ property_desc_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_9__ {int /*<<< orphan*/  setter; int /*<<< orphan*/  getter; } ;
struct TYPE_10__ {TYPE_1__ accessor; } ;
struct TYPE_12__ {int type; int flags; TYPE_2__ u; } ;
typedef  TYPE_4__ dispex_prop_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int PROPF_CONFIGURABLE ; 
 int PROPF_ENUMERABLE ; 
 int PROPF_WRITABLE ; 
#define  PROP_ACCESSOR 130 
#define  PROP_BUILTIN 129 
#define  PROP_JSVAL 128 
 int /*<<< orphan*/  S_OK ; 
 void* TRUE ; 
 int /*<<< orphan*/  find_prop_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_4__**) ; 
 int /*<<< orphan*/ * jsdisp_addref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prop_get (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_hash (int /*<<< orphan*/  const*) ; 

HRESULT jsdisp_get_own_property(jsdisp_t *obj, const WCHAR *name, BOOL flags_only,
                                property_desc_t *desc)
{
    dispex_prop_t *prop;
    HRESULT hres;

    hres = find_prop_name(obj, string_hash(name), name, &prop);
    if(FAILED(hres))
        return hres;

    if(!prop)
        return DISP_E_UNKNOWNNAME;

    memset(desc, 0, sizeof(*desc));

    switch(prop->type) {
    case PROP_BUILTIN:
    case PROP_JSVAL:
        desc->mask |= PROPF_WRITABLE;
        desc->explicit_value = TRUE;
        if(!flags_only) {
            hres = prop_get(obj, prop, &desc->value);
            if(FAILED(hres))
                return hres;
        }
        break;
    case PROP_ACCESSOR:
        desc->explicit_getter = desc->explicit_setter = TRUE;
        if(!flags_only) {
            desc->getter = prop->u.accessor.getter
                ? jsdisp_addref(prop->u.accessor.getter) : NULL;
            desc->setter = prop->u.accessor.setter
                ? jsdisp_addref(prop->u.accessor.setter) : NULL;
        }
        break;
    default:
        return DISP_E_UNKNOWNNAME;
    }

    desc->flags = prop->flags & (PROPF_ENUMERABLE | PROPF_WRITABLE | PROPF_CONFIGURABLE);
    desc->mask |= PROPF_ENUMERABLE | PROPF_CONFIGURABLE;
    return S_OK;
}