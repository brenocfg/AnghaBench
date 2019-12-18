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
typedef  int /*<<< orphan*/  custom_ext_parse_cb_wrap ;
struct TYPE_7__ {int meths_count; TYPE_2__* meths; } ;
typedef  TYPE_1__ custom_ext_methods ;
struct TYPE_8__ {scalar_t__ add_cb; struct TYPE_8__* parse_arg; struct TYPE_8__* add_arg; } ;
typedef  TYPE_2__ custom_ext_method ;
typedef  int /*<<< orphan*/  custom_ext_add_cb_wrap ;

/* Variables and functions */
 void* OPENSSL_memdup (TYPE_2__*,int) ; 
 scalar_t__ custom_ext_add_old_cb_wrap ; 
 int /*<<< orphan*/  custom_exts_free (TYPE_1__*) ; 

int custom_exts_copy(custom_ext_methods *dst, const custom_ext_methods *src)
{
    size_t i;
    int err = 0;

    if (src->meths_count > 0) {
        dst->meths =
            OPENSSL_memdup(src->meths,
                           sizeof(*src->meths) * src->meths_count);
        if (dst->meths == NULL)
            return 0;
        dst->meths_count = src->meths_count;

        for (i = 0; i < src->meths_count; i++) {
            custom_ext_method *methsrc = src->meths + i;
            custom_ext_method *methdst = dst->meths + i;

            if (methsrc->add_cb != custom_ext_add_old_cb_wrap)
                continue;

            /*
             * We have found an old style API wrapper. We need to copy the
             * arguments too.
             */

            if (err) {
                methdst->add_arg = NULL;
                methdst->parse_arg = NULL;
                continue;
            }

            methdst->add_arg = OPENSSL_memdup(methsrc->add_arg,
                                              sizeof(custom_ext_add_cb_wrap));
            methdst->parse_arg = OPENSSL_memdup(methsrc->parse_arg,
                                            sizeof(custom_ext_parse_cb_wrap));

            if (methdst->add_arg == NULL || methdst->parse_arg == NULL)
                err = 1;
        }
    }

    if (err) {
        custom_exts_free(dst);
        return 0;
    }

    return 1;
}