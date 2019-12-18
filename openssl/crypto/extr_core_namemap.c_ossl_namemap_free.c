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
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  namenum; scalar_t__ stored; } ;
typedef  TYPE_1__ OSSL_NAMEMAP ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  lh_NAMENUM_ENTRY_doall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lh_NAMENUM_ENTRY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namenum_free ; 

void ossl_namemap_free(OSSL_NAMEMAP *namemap)
{
    if (namemap == NULL || namemap->stored)
        return;

    lh_NAMENUM_ENTRY_doall(namemap->namenum, namenum_free);
    lh_NAMENUM_ENTRY_free(namemap->namenum);

    CRYPTO_THREAD_lock_free(namemap->lock);
    OPENSSL_free(namemap);
}