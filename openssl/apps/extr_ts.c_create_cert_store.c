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
typedef  int /*<<< orphan*/  X509_VERIFY_PARAM ;
typedef  int /*<<< orphan*/  X509_STORE ;
typedef  int /*<<< orphan*/  X509_LOOKUP ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  X509_FILETYPE_PEM ; 
 int /*<<< orphan*/  X509_LOOKUP_add_dir (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_LOOKUP_file () ; 
 int /*<<< orphan*/  X509_LOOKUP_hash_dir () ; 
 int /*<<< orphan*/  X509_LOOKUP_load_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_LOOKUP_load_store (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  X509_LOOKUP_store () ; 
 int /*<<< orphan*/ * X509_STORE_add_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_STORE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_new () ; 
 int /*<<< orphan*/  X509_STORE_set1_param (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_STORE_set_verify_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  verify_cb ; 

__attribute__((used)) static X509_STORE *create_cert_store(const char *CApath, const char *CAfile,
                                     const char *CAstore, X509_VERIFY_PARAM *vpm)
{
    X509_STORE *cert_ctx = NULL;
    X509_LOOKUP *lookup = NULL;

    cert_ctx = X509_STORE_new();
    X509_STORE_set_verify_cb(cert_ctx, verify_cb);
    if (CApath != NULL) {
        lookup = X509_STORE_add_lookup(cert_ctx, X509_LOOKUP_hash_dir());
        if (lookup == NULL) {
            BIO_printf(bio_err, "memory allocation failure\n");
            goto err;
        }
        if (!X509_LOOKUP_add_dir(lookup, CApath, X509_FILETYPE_PEM)) {
            BIO_printf(bio_err, "Error loading directory %s\n", CApath);
            goto err;
        }
    }

    if (CAfile != NULL) {
        lookup = X509_STORE_add_lookup(cert_ctx, X509_LOOKUP_file());
        if (lookup == NULL) {
            BIO_printf(bio_err, "memory allocation failure\n");
            goto err;
        }
        if (!X509_LOOKUP_load_file(lookup, CAfile, X509_FILETYPE_PEM)) {
            BIO_printf(bio_err, "Error loading file %s\n", CAfile);
            goto err;
        }
    }

    if (CAstore != NULL) {
        lookup = X509_STORE_add_lookup(cert_ctx, X509_LOOKUP_store());
        if (lookup == NULL) {
            BIO_printf(bio_err, "memory allocation failure\n");
            goto err;
        }
        if (!X509_LOOKUP_load_store(lookup, CAstore)) {
            BIO_printf(bio_err, "Error loading store URI %s\n", CAstore);
            goto err;
        }
    }

    if (vpm != NULL)
        X509_STORE_set1_param(cert_ctx, vpm);

    return cert_ctx;

 err:
    X509_STORE_free(cert_ctx);
    return NULL;
}