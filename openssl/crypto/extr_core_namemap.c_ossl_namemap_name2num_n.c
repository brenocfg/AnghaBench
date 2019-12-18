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
struct TYPE_8__ {int number; int /*<<< orphan*/ * name; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  namenum; } ;
typedef  TYPE_1__ OSSL_NAMEMAP ;
typedef  TYPE_2__ NAMENUM_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_read_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_strndup (char const*,size_t) ; 
 TYPE_2__* lh_NAMENUM_ENTRY_retrieve (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* ossl_namemap_stored (int /*<<< orphan*/ *) ; 

int ossl_namemap_name2num_n(const OSSL_NAMEMAP *namemap,
                            const char *name, size_t name_len)
{
    NAMENUM_ENTRY *namenum_entry, namenum_tmpl;
    int number = 0;

#ifndef FIPS_MODE
    if (namemap == NULL)
        namemap = ossl_namemap_stored(NULL);
#endif

    if (namemap == NULL)
        return 0;

    if ((namenum_tmpl.name = OPENSSL_strndup(name, name_len)) == NULL)
        return 0;
    namenum_tmpl.number = 0;
    CRYPTO_THREAD_read_lock(namemap->lock);
    namenum_entry =
        lh_NAMENUM_ENTRY_retrieve(namemap->namenum, &namenum_tmpl);
    if (namenum_entry != NULL)
        number = namenum_entry->number;
    CRYPTO_THREAD_unlock(namemap->lock);
    OPENSSL_free(namenum_tmpl.name);

    return number;
}