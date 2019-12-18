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
struct TYPE_5__ {int type; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ BIO_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_F_BIO_METH_NEW ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/ * OPENSSL_strdup (char const*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

BIO_METHOD *BIO_meth_new(int type, const char *name)
{
    BIO_METHOD *biom = OPENSSL_zalloc(sizeof(BIO_METHOD));

    if (biom == NULL
            || (biom->name = OPENSSL_strdup(name)) == NULL) {
        OPENSSL_free(biom);
        BIOerr(BIO_F_BIO_METH_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    biom->type = type;
    return biom;
}