#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* desc; } ;
typedef  TYPE_4__ vbdisp_t ;
typedef  size_t vbdisp_invoke_type_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {unsigned int func_cnt; TYPE_2__* funcs; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; TYPE_1__** entries; int /*<<< orphan*/  is_public; } ;
struct TYPE_6__ {int /*<<< orphan*/  is_public; } ;
typedef  unsigned int DISPID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 size_t VBDISP_ANY ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static BOOL get_func_id(vbdisp_t *This, const WCHAR *name, vbdisp_invoke_type_t invoke_type, BOOL search_private, DISPID *id)
{
    unsigned i;

    for(i = invoke_type == VBDISP_ANY ? 0 : 1; i < This->desc->func_cnt; i++) {
        if(invoke_type == VBDISP_ANY) {
            if(!search_private && !This->desc->funcs[i].is_public)
                continue;
            if(!i && !This->desc->funcs[0].name) /* default value may not exist */
                continue;
        }else {
            if(!This->desc->funcs[i].entries[invoke_type]
                || (!search_private && !This->desc->funcs[i].entries[invoke_type]->is_public))
                continue;
        }

        if(!strcmpiW(This->desc->funcs[i].name, name)) {
            *id = i;
            return TRUE;
        }
    }

    return FALSE;
}