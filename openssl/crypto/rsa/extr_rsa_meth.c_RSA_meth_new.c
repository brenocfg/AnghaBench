#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ RSA_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/ * OPENSSL_strdup (char const*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  RSA_F_RSA_METH_NEW ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

RSA_METHOD *RSA_meth_new(const char *name, int flags)
{
    RSA_METHOD *meth = OPENSSL_zalloc(sizeof(*meth));

    if (meth != NULL) {
        meth->flags = flags;

        meth->name = OPENSSL_strdup(name);
        if (meth->name != NULL)
            return meth;

        OPENSSL_free(meth);
    }

    RSAerr(RSA_F_RSA_METH_NEW, ERR_R_MALLOC_FAILURE);
    return NULL;
}