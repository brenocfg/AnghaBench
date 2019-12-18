#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  X509_STORE ;
typedef  int /*<<< orphan*/  X509_LOOKUP ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  X509_FILETYPE_DEFAULT ; 
 int /*<<< orphan*/  X509_FILETYPE_PEM ; 
 int /*<<< orphan*/  X509_LOOKUP_add_dir (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_LOOKUP_add_store (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  X509_LOOKUP_file () ; 
 int /*<<< orphan*/  X509_LOOKUP_hash_dir () ; 
 int /*<<< orphan*/  X509_LOOKUP_load_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_LOOKUP_store () ; 
 int /*<<< orphan*/ * X509_STORE_add_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_STORE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_new () ; 
 int /*<<< orphan*/  bio_err ; 

X509_STORE *setup_verify(const char *CAfile, int noCAfile,
                         const char *CApath, int noCApath,
                         const char *CAstore, int noCAstore)
{
    X509_STORE *store = X509_STORE_new();
    X509_LOOKUP *lookup;

    if (store == NULL)
        goto end;

    if (CAfile != NULL || !noCAfile) {
        lookup = X509_STORE_add_lookup(store, X509_LOOKUP_file());
        if (lookup == NULL)
            goto end;
        if (CAfile != NULL) {
            if (!X509_LOOKUP_load_file(lookup, CAfile, X509_FILETYPE_PEM)) {
                BIO_printf(bio_err, "Error loading file %s\n", CAfile);
                goto end;
            }
        } else {
            X509_LOOKUP_load_file(lookup, NULL, X509_FILETYPE_DEFAULT);
        }
    }

    if (CApath != NULL || !noCApath) {
        lookup = X509_STORE_add_lookup(store, X509_LOOKUP_hash_dir());
        if (lookup == NULL)
            goto end;
        if (CApath != NULL) {
            if (!X509_LOOKUP_add_dir(lookup, CApath, X509_FILETYPE_PEM)) {
                BIO_printf(bio_err, "Error loading directory %s\n", CApath);
                goto end;
            }
        } else {
            X509_LOOKUP_add_dir(lookup, NULL, X509_FILETYPE_DEFAULT);
        }
    }

    if (CAstore != NULL || !noCAstore) {
        lookup = X509_STORE_add_lookup(store, X509_LOOKUP_store());
        if (lookup == NULL)
            goto end;
        if (!X509_LOOKUP_add_store(lookup, CAstore)) {
            if (CAstore != NULL)
                BIO_printf(bio_err, "Error loading store URI %s\n", CAstore);
            goto end;
        }
    }

    ERR_clear_error();
    return store;
 end:
    X509_STORE_free(store);
    return NULL;
}