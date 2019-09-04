#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  custom_ext_methods ;
struct TYPE_6__ {int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ custom_ext_method ;
struct TYPE_7__ {unsigned int type; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  RAW_EXTENSION ;
typedef  TYPE_2__ EXTENSION_DEFINITION ;
typedef  int /*<<< orphan*/  ENDPOINT ;

/* Variables and functions */
 int /*<<< orphan*/  ENDPOINT_BOTH ; 
 int /*<<< orphan*/  ENDPOINT_CLIENT ; 
 int /*<<< orphan*/  ENDPOINT_SERVER ; 
 size_t OSSL_NELEM (TYPE_2__*) ; 
 unsigned int SSL_EXT_CLIENT_HELLO ; 
 unsigned int SSL_EXT_TLS1_2_SERVER_HELLO ; 
 TYPE_1__* custom_ext_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,size_t*) ; 
 TYPE_2__* ext_defs ; 
 int /*<<< orphan*/  validate_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int verify_extension(SSL *s, unsigned int context, unsigned int type,
                            custom_ext_methods *meths, RAW_EXTENSION *rawexlist,
                            RAW_EXTENSION **found)
{
    size_t i;
    size_t builtin_num = OSSL_NELEM(ext_defs);
    const EXTENSION_DEFINITION *thisext;

    for (i = 0, thisext = ext_defs; i < builtin_num; i++, thisext++) {
        if (type == thisext->type) {
            if (!validate_context(s, thisext->context, context))
                return 0;

            *found = &rawexlist[i];
            return 1;
        }
    }

    /* Check the custom extensions */
    if (meths != NULL) {
        size_t offset = 0;
        ENDPOINT role = ENDPOINT_BOTH;
        custom_ext_method *meth = NULL;

        if ((context & SSL_EXT_CLIENT_HELLO) != 0)
            role = ENDPOINT_SERVER;
        else if ((context & SSL_EXT_TLS1_2_SERVER_HELLO) != 0)
            role = ENDPOINT_CLIENT;

        meth = custom_ext_find(meths, role, type, &offset);
        if (meth != NULL) {
            if (!validate_context(s, meth->context, context))
                return 0;
            *found = &rawexlist[offset + builtin_num];
            return 1;
        }
    }

    /* Unknown extension. We allow it */
    *found = NULL;
    return 1;
}