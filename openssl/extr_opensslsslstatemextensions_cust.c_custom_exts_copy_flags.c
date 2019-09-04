#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t meths_count; TYPE_2__* meths; } ;
typedef  TYPE_1__ custom_ext_methods ;
struct TYPE_8__ {int /*<<< orphan*/  ext_flags; int /*<<< orphan*/  ext_type; int /*<<< orphan*/  role; } ;
typedef  TYPE_2__ custom_ext_method ;

/* Variables and functions */
 TYPE_2__* custom_ext_find (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int custom_exts_copy_flags(custom_ext_methods *dst,
                           const custom_ext_methods *src)
{
    size_t i;
    custom_ext_method *methsrc = src->meths;

    for (i = 0; i < src->meths_count; i++, methsrc++) {
        custom_ext_method *methdst = custom_ext_find(dst, methsrc->role,
                                                     methsrc->ext_type, NULL);

        if (methdst == NULL)
            continue;

        methdst->ext_flags = methsrc->ext_flags;
    }

    return 1;
}