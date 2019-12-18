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
struct TYPE_4__ {size_t meths_count; TYPE_2__* meths; } ;
typedef  TYPE_1__ custom_ext_methods ;
struct TYPE_5__ {scalar_t__ ext_flags; } ;
typedef  TYPE_2__ custom_ext_method ;

/* Variables and functions */

void custom_ext_init(custom_ext_methods *exts)
{
    size_t i;
    custom_ext_method *meth = exts->meths;

    for (i = 0; i < exts->meths_count; i++, meth++)
        meth->ext_flags = 0;
}