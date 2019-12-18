#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* builtin_info; TYPE_1__* ctx; } ;
typedef  TYPE_3__ jsdisp_t ;
struct TYPE_10__ {unsigned int flags; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ builtin_prop_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {int props_cnt; TYPE_4__ const* props; } ;
struct TYPE_7__ {unsigned int version; int /*<<< orphan*/  html_mode; } ;

/* Variables and functions */
 int PROPF_HTML ; 
 unsigned int PROPF_VERSION_MASK ; 
 unsigned int PROPF_VERSION_SHIFT ; 
 int wcscmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const builtin_prop_t *find_builtin_prop(jsdisp_t *This, const WCHAR *name)
{
    int min = 0, max, i, r;

    max = This->builtin_info->props_cnt-1;
    while(min <= max) {
        i = (min+max)/2;

        r = wcscmp(name, This->builtin_info->props[i].name);
        if(!r) {
            /* Skip prop if it's available only in higher compatibility mode. */
            unsigned version = (This->builtin_info->props[i].flags & PROPF_VERSION_MASK)
                >> PROPF_VERSION_SHIFT;
            if(version && version > This->ctx->version)
                return NULL;

            /* Skip prop if it's available only in HTML mode and we're not running in HTML mode. */
            if((This->builtin_info->props[i].flags & PROPF_HTML) && !This->ctx->html_mode)
                return NULL;

            return This->builtin_info->props + i;
        }

        if(r < 0)
            max = i-1;
        else
            min = i+1;
    }

    return NULL;
}