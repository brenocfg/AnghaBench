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
struct TYPE_5__ {int type; int pkey_type; int refcnt; int /*<<< orphan*/ * lock; } ;
typedef  TYPE_1__ EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

EVP_MD *EVP_MD_meth_new(int md_type, int pkey_type)
{
    EVP_MD *md = OPENSSL_zalloc(sizeof(*md));

    if (md != NULL) {
        md->type = md_type;
        md->pkey_type = pkey_type;
        md->lock = CRYPTO_THREAD_lock_new();
        if (md->lock == NULL) {
            OPENSSL_free(md);
            return NULL;
        }
        md->refcnt = 1;
    }
    return md;
}