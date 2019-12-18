#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * subjectAltNames; } ;
typedef  TYPE_1__ OSSL_CMP_CTX ;
typedef  int /*<<< orphan*/  GENERAL_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_R_MULTIPLE_SAN_SOURCES ; 
 int /*<<< orphan*/  CMP_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CMPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GENERAL_NAME_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  GENERAL_NAME_free (int /*<<< orphan*/ *) ; 
 int OSSL_CMP_CTX_reqExtensions_have_SAN (TYPE_1__*) ; 
 int /*<<< orphan*/ * sk_GENERAL_NAME_new_null () ; 
 int /*<<< orphan*/  sk_GENERAL_NAME_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int OSSL_CMP_CTX_push1_subjectAltName(OSSL_CMP_CTX *ctx,
                                      const GENERAL_NAME *name)
{
    GENERAL_NAME *name_dup;

    if (ctx == NULL || name == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }

    if (OSSL_CMP_CTX_reqExtensions_have_SAN(ctx) == 1) {
        CMPerr(0, CMP_R_MULTIPLE_SAN_SOURCES);
        return 0;
    }

    if (ctx->subjectAltNames == NULL
            && (ctx->subjectAltNames = sk_GENERAL_NAME_new_null()) == NULL)
        return 0;
    if ((name_dup = GENERAL_NAME_dup(name)) == NULL)
        return 0;
    if (!sk_GENERAL_NAME_push(ctx->subjectAltNames, name_dup)) {
        GENERAL_NAME_free(name_dup);
        return 0;
    }
    return 1;
}