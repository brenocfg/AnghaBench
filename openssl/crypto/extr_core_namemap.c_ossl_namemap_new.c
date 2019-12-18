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
struct TYPE_5__ {int /*<<< orphan*/ * namenum; int /*<<< orphan*/ * lock; } ;
typedef  TYPE_1__ OSSL_NAMEMAP ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/ * lh_NAMENUM_ENTRY_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namenum_cmp ; 
 int /*<<< orphan*/  namenum_hash ; 
 int /*<<< orphan*/  ossl_namemap_free (TYPE_1__*) ; 

OSSL_NAMEMAP *ossl_namemap_new(void)
{
    OSSL_NAMEMAP *namemap;

    if ((namemap = OPENSSL_zalloc(sizeof(*namemap))) != NULL
        && (namemap->lock = CRYPTO_THREAD_lock_new()) != NULL
        && (namemap->namenum =
            lh_NAMENUM_ENTRY_new(namenum_hash, namenum_cmp)) != NULL)
        return namemap;

    ossl_namemap_free(namemap);
    return NULL;
}