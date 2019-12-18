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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {TYPE_1__* jsregexp; int /*<<< orphan*/ * str; } ;
struct TYPE_4__ {unsigned int flags; } ;
typedef  TYPE_2__ RegExpInstance ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSCLASS_REGEXP ; 
 int /*<<< orphan*/  create_regexp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  debugstr_jsval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iface_to_jsdisp (int /*<<< orphan*/ ) ; 
 scalar_t__ is_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_flatten (int /*<<< orphan*/ *) ; 
 unsigned int jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_regexp_flags (int /*<<< orphan*/  const*,unsigned int,unsigned int*) ; 
 TYPE_2__* regexp_from_jsdisp (int /*<<< orphan*/ *) ; 

HRESULT create_regexp_var(script_ctx_t *ctx, jsval_t src_arg, jsval_t *flags_arg, jsdisp_t **ret)
{
    unsigned flags, opt_len = 0;
    const WCHAR *opt = NULL;
    jsstr_t *src;
    HRESULT hres;

    if(is_object_instance(src_arg)) {
        jsdisp_t *obj;

        obj = iface_to_jsdisp(get_object(src_arg));
        if(obj) {
            if(is_class(obj, JSCLASS_REGEXP)) {
                RegExpInstance *regexp = regexp_from_jsdisp(obj);

                hres = create_regexp(ctx, regexp->str, regexp->jsregexp->flags, ret);
                jsdisp_release(obj);
                return hres;
            }

            jsdisp_release(obj);
        }
    }

    if(!is_string(src_arg)) {
        FIXME("src_arg = %s\n", debugstr_jsval(src_arg));
        return E_NOTIMPL;
    }

    src = get_string(src_arg);

    if(flags_arg) {
        jsstr_t *opt_str;

        if(!is_string(*flags_arg)) {
            FIXME("unimplemented for %s\n", debugstr_jsval(*flags_arg));
            return E_NOTIMPL;
        }

        opt_str = get_string(*flags_arg);
        opt = jsstr_flatten(opt_str);
        if(!opt)
            return E_OUTOFMEMORY;
        opt_len = jsstr_length(opt_str);
    }

    hres = parse_regexp_flags(opt, opt_len, &flags);
    if(FAILED(hres))
        return hres;

    return create_regexp(ctx, src, flags, ret);
}