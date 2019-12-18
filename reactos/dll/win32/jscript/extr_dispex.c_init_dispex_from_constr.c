#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ dispex_prop_t ;
typedef  int /*<<< orphan*/  builtin_info_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ PROP_DELETED ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_prop_name_prot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,TYPE_1__**) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iface_to_jsdisp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prop_get (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_hash (char const*) ; 

HRESULT init_dispex_from_constr(jsdisp_t *dispex, script_ctx_t *ctx, const builtin_info_t *builtin_info, jsdisp_t *constr)
{
    jsdisp_t *prot = NULL;
    dispex_prop_t *prop;
    HRESULT hres;

    static const WCHAR prototypeW[] = {'p','r','o','t','o','t','y','p','e',0};

    hres = find_prop_name_prot(constr, string_hash(prototypeW), prototypeW, &prop);
    if(SUCCEEDED(hres) && prop && prop->type!=PROP_DELETED) {
        jsval_t val;

        hres = prop_get(constr, prop, &val);
        if(FAILED(hres)) {
            ERR("Could not get prototype\n");
            return hres;
        }

        if(is_object_instance(val))
            prot = iface_to_jsdisp(get_object(val));
        jsval_release(val);
    }

    hres = init_dispex(dispex, ctx, builtin_info, prot);

    if(prot)
        jsdisp_release(prot);
    return hres;
}