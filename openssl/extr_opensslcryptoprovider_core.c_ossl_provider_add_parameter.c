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
struct TYPE_8__ {struct TYPE_8__* value; struct TYPE_8__* name; } ;
struct TYPE_7__ {int /*<<< orphan*/ * parameters; } ;
typedef  TYPE_1__ OSSL_PROVIDER ;
typedef  TYPE_2__ INFOPAIR ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_OSSL_PROVIDER_ADD_PARAMETER ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 void* OPENSSL_strdup (char const*) ; 
 TYPE_2__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/ * sk_INFOPAIR_new_null () ; 
 scalar_t__ sk_INFOPAIR_push (int /*<<< orphan*/ *,TYPE_2__*) ; 

int ossl_provider_add_parameter(OSSL_PROVIDER *prov,
                                const char *name, const char *value)
{
    INFOPAIR *pair = NULL;

    if ((pair = OPENSSL_zalloc(sizeof(*pair))) != NULL
        && (prov->parameters != NULL
            || (prov->parameters = sk_INFOPAIR_new_null()) != NULL)
        && (pair->name = OPENSSL_strdup(name)) != NULL
        && (pair->value = OPENSSL_strdup(value)) != NULL
        && sk_INFOPAIR_push(prov->parameters, pair) > 0)
        return 1;

    if (pair != NULL) {
        OPENSSL_free(pair->name);
        OPENSSL_free(pair->value);
        OPENSSL_free(pair);
    }
    CRYPTOerr(CRYPTO_F_OSSL_PROVIDER_ADD_PARAMETER, ERR_R_MALLOC_FAILURE);
    return 0;
}