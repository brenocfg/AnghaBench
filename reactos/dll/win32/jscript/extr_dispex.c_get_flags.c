#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* prototype; } ;
typedef  TYPE_2__ jsdisp_t ;
struct TYPE_8__ {int /*<<< orphan*/  ref; } ;
struct TYPE_10__ {scalar_t__ type; int /*<<< orphan*/  flags; TYPE_1__ u; } ;
typedef  TYPE_3__ dispex_prop_t ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ PROP_DELETED ; 
 scalar_t__ PROP_PROTREF ; 
 TYPE_3__* get_prop (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD get_flags(jsdisp_t *This, dispex_prop_t *prop)
{
    if(prop->type == PROP_PROTREF) {
        dispex_prop_t *parent = get_prop(This->prototype, prop->u.ref);
        if(!parent) {
            prop->type = PROP_DELETED;
            return 0;
        }

        return get_flags(This->prototype, parent);
    }

    return prop->flags;
}