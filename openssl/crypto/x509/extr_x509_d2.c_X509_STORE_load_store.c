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
 scalar_t__ X509_LOOKUP_add_store (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  X509_LOOKUP_store () ; 
 int /*<<< orphan*/ * X509_STORE_add_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int X509_STORE_load_store(X509_STORE *ctx, const char *uri)
{
    X509_LOOKUP *lookup;

    if (uri == NULL
        || (lookup = X509_STORE_add_lookup(ctx, X509_LOOKUP_store())) == NULL
        || X509_LOOKUP_add_store(lookup, uri) == 0)
        return 0;

    return 1;
}