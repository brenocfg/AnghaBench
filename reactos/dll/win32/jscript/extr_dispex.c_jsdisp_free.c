#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ setter; scalar_t__ getter; } ;
struct TYPE_11__ {TYPE_1__ accessor; int /*<<< orphan*/  val; } ;
struct TYPE_13__ {int prop_cnt; int type; TYPE_3__* builtin_info; scalar_t__ prototype; int /*<<< orphan*/  ctx; struct TYPE_13__* props; struct TYPE_13__* name; TYPE_2__ u; } ;
typedef  TYPE_4__ jsdisp_t ;
typedef  TYPE_4__ dispex_prop_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* destructor ) (TYPE_4__*) ;} ;

/* Variables and functions */
#define  PROP_ACCESSOR 129 
#define  PROP_JSVAL 128 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*) ; 
 int /*<<< orphan*/  heap_free (TYPE_4__*) ; 
 int /*<<< orphan*/  jsdisp_release (scalar_t__) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  script_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

void jsdisp_free(jsdisp_t *obj)
{
    dispex_prop_t *prop;

    TRACE("(%p)\n", obj);

    for(prop = obj->props; prop < obj->props+obj->prop_cnt; prop++) {
        switch(prop->type) {
        case PROP_JSVAL:
            jsval_release(prop->u.val);
            break;
        case PROP_ACCESSOR:
            if(prop->u.accessor.getter)
                jsdisp_release(prop->u.accessor.getter);
            if(prop->u.accessor.setter)
                jsdisp_release(prop->u.accessor.setter);
            break;
        default:
            break;
        };
        heap_free(prop->name);
    }
    heap_free(obj->props);
    script_release(obj->ctx);
    if(obj->prototype)
        jsdisp_release(obj->prototype);

    if(obj->builtin_info->destructor)
        obj->builtin_info->destructor(obj);
    else
        heap_free(obj);
}