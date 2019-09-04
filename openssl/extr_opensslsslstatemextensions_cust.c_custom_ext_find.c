#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t meths_count; TYPE_2__* meths; } ;
typedef  TYPE_1__ custom_ext_methods ;
struct TYPE_6__ {unsigned int ext_type; scalar_t__ role; } ;
typedef  TYPE_2__ custom_ext_method ;
typedef  scalar_t__ ENDPOINT ;

/* Variables and functions */
 scalar_t__ ENDPOINT_BOTH ; 

custom_ext_method *custom_ext_find(const custom_ext_methods *exts,
                                   ENDPOINT role, unsigned int ext_type,
                                   size_t *idx)
{
    size_t i;
    custom_ext_method *meth = exts->meths;

    for (i = 0; i < exts->meths_count; i++, meth++) {
        if (ext_type == meth->ext_type
                && (role == ENDPOINT_BOTH || role == meth->role
                    || meth->role == ENDPOINT_BOTH)) {
            if (idx != NULL)
                *idx = i;
            return meth;
        }
    }
    return NULL;
}