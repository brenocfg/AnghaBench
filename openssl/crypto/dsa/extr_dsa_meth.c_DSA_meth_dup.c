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
typedef  TYPE_1__ DSA_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_F_DSA_METH_DUP ; 
 int /*<<< orphan*/  DSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/ * OPENSSL_strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 

DSA_METHOD *DSA_meth_dup(const DSA_METHOD *dsam)
{
    DSA_METHOD *ret = OPENSSL_malloc(sizeof(*ret));

    if (ret != NULL) {
        memcpy(ret, dsam, sizeof(*dsam));

        ret->name = OPENSSL_strdup(dsam->name);
        if (ret->name != NULL)
            return ret;

        OPENSSL_free(ret);
    }

    DSAerr(DSA_F_DSA_METH_DUP, ERR_R_MALLOC_FAILURE);
    return NULL;
}