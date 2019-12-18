#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_LOOKUP ;
struct TYPE_3__ {int /*<<< orphan*/  cert_store; } ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_pop_to_mark () ; 
 int /*<<< orphan*/  ERR_set_mark () ; 
 int /*<<< orphan*/  X509_FILETYPE_DEFAULT ; 
 int /*<<< orphan*/  X509_LOOKUP_add_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_LOOKUP_hash_dir () ; 
 int /*<<< orphan*/ * X509_STORE_add_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int SSL_CTX_set_default_verify_dir(SSL_CTX *ctx)
{
    X509_LOOKUP *lookup;

    lookup = X509_STORE_add_lookup(ctx->cert_store, X509_LOOKUP_hash_dir());
    if (lookup == NULL)
        return 0;

    /* We ignore errors, in case the directory doesn't exist */
    ERR_set_mark();

    X509_LOOKUP_add_dir(lookup, NULL, X509_FILETYPE_DEFAULT);

    ERR_pop_to_mark();

    return 1;
}