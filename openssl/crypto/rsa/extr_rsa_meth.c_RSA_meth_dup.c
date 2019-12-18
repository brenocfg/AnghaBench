#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ RSA_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/ * OPENSSL_strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_F_RSA_METH_DUP ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 

RSA_METHOD *RSA_meth_dup(const RSA_METHOD *meth)
{
    RSA_METHOD *ret = OPENSSL_malloc(sizeof(*ret));

    if (ret != NULL) {
        memcpy(ret, meth, sizeof(*meth));

        ret->name = OPENSSL_strdup(meth->name);
        if (ret->name != NULL)
            return ret;

        OPENSSL_free(ret);
    }

    RSAerr(RSA_F_RSA_METH_DUP, ERR_R_MALLOC_FAILURE);
    return NULL;
}