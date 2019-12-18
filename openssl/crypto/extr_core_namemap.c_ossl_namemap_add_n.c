#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int number; int /*<<< orphan*/ * name; } ;
struct TYPE_9__ {int max_number; int /*<<< orphan*/  lock; int /*<<< orphan*/  namenum; } ;
typedef  TYPE_1__ OSSL_NAMEMAP ;
typedef  TYPE_2__ NAMENUM_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OPENSSL_strndup (char const*,size_t) ; 
 TYPE_2__* OPENSSL_zalloc (int) ; 
 scalar_t__ lh_NAMENUM_ENTRY_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lh_NAMENUM_ENTRY_insert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  namenum_free (TYPE_2__*) ; 
 int ossl_namemap_name2num_n (TYPE_1__*,char const*,size_t) ; 
 TYPE_1__* ossl_namemap_stored (int /*<<< orphan*/ *) ; 

int ossl_namemap_add_n(OSSL_NAMEMAP *namemap, int number,
                       const char *name, size_t name_len)
{
    NAMENUM_ENTRY *namenum = NULL;
    int tmp_number;

#ifndef FIPS_MODE
    if (namemap == NULL)
        namemap = ossl_namemap_stored(NULL);
#endif

    if (name == NULL || name_len == 0 || namemap == NULL)
        return 0;

    if ((tmp_number = ossl_namemap_name2num_n(namemap, name, name_len)) != 0)
        return tmp_number;       /* Pretend success */

    CRYPTO_THREAD_write_lock(namemap->lock);

    if ((namenum = OPENSSL_zalloc(sizeof(*namenum))) == NULL
        || (namenum->name = OPENSSL_strndup(name, name_len)) == NULL)
        goto err;

    namenum->number = tmp_number =
        number != 0 ? number : ++namemap->max_number;
    (void)lh_NAMENUM_ENTRY_insert(namemap->namenum, namenum);

    if (lh_NAMENUM_ENTRY_error(namemap->namenum))
        goto err;

    CRYPTO_THREAD_unlock(namemap->lock);

    return tmp_number;

 err:
    namenum_free(namenum);

    CRYPTO_THREAD_unlock(namemap->lock);
    return 0;
}