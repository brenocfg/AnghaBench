#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_1__* builtin_info; TYPE_4__* props; } ;
typedef  TYPE_3__ jsdisp_t ;
struct TYPE_15__ {unsigned int idx; TYPE_5__ const* p; } ;
struct TYPE_17__ {unsigned int bucket_head; unsigned int bucket_next; TYPE_2__ u; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ dispex_prop_t ;
struct TYPE_18__ {unsigned int flags; scalar_t__ setter; } ;
typedef  TYPE_5__ builtin_prop_t ;
typedef  unsigned int WCHAR ;
struct TYPE_14__ {unsigned int (* idx_length ) (TYPE_3__*) ;scalar_t__ idx_put; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 unsigned int PROPF_CONFIGURABLE ; 
 unsigned int PROPF_ENUMERABLE ; 
 unsigned int PROPF_METHOD ; 
 unsigned int PROPF_WRITABLE ; 
 int /*<<< orphan*/  PROP_BUILTIN ; 
 int /*<<< orphan*/  PROP_IDX ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_4__* alloc_prop (TYPE_3__*,unsigned int const*,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_5__* find_builtin_prop (TYPE_3__*,unsigned int const*) ; 
 unsigned int get_props_idx (TYPE_3__*,unsigned int) ; 
 scalar_t__ iswdigit (unsigned int const) ; 
 unsigned int stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  wcscmp (unsigned int const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT find_prop_name(jsdisp_t *This, unsigned hash, const WCHAR *name, dispex_prop_t **ret)
{
    const builtin_prop_t *builtin;
    unsigned bucket, pos, prev = 0;
    dispex_prop_t *prop;

    bucket = get_props_idx(This, hash);
    pos = This->props[bucket].bucket_head;
    while(pos != 0) {
        if(!wcscmp(name, This->props[pos].name)) {
            if(prev != 0) {
                This->props[prev].bucket_next = This->props[pos].bucket_next;
                This->props[pos].bucket_next = This->props[bucket].bucket_head;
                This->props[bucket].bucket_head = pos;
            }

            *ret = &This->props[pos];
            return S_OK;
        }

        prev = pos;
        pos = This->props[pos].bucket_next;
    }

    builtin = find_builtin_prop(This, name);
    if(builtin) {
        unsigned flags = builtin->flags;
        if(flags & PROPF_METHOD)
            flags |= PROPF_WRITABLE | PROPF_CONFIGURABLE;
        else if(builtin->setter)
            flags |= PROPF_WRITABLE;
        flags &= PROPF_ENUMERABLE | PROPF_WRITABLE | PROPF_CONFIGURABLE;
        prop = alloc_prop(This, name, PROP_BUILTIN, flags);
        if(!prop)
            return E_OUTOFMEMORY;

        prop->u.p = builtin;
        *ret = prop;
        return S_OK;
    }

    if(This->builtin_info->idx_length) {
        const WCHAR *ptr;
        unsigned idx = 0;

        for(ptr = name; iswdigit(*ptr) && idx < 0x10000; ptr++)
            idx = idx*10 + (*ptr-'0');
        if(!*ptr && idx < This->builtin_info->idx_length(This)) {
            prop = alloc_prop(This, name, PROP_IDX, This->builtin_info->idx_put ? PROPF_WRITABLE : 0);
            if(!prop)
                return E_OUTOFMEMORY;

            prop->u.idx = idx;
            *ret = prop;
            return S_OK;
        }
    }

    *ret = NULL;
    return S_OK;
}