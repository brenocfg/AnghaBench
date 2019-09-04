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
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 size_t OSSL_NELEM (char const* const*) ; 
 void* ossl_property_false ; 
 scalar_t__ ossl_property_name (int /*<<< orphan*/ *,char const* const,int) ; 
 void* ossl_property_true ; 
 void* ossl_property_value (int /*<<< orphan*/ *,char*,int) ; 

int ossl_property_parse_init(OPENSSL_CTX *ctx)
{
    static const char *const predefined_names[] = {
        "default",      /* Being provided by the default built-in provider */
        "legacy",       /* Provided by the legacy provider */
        "provider",     /* Name of provider (default, fips) */
        "version",      /* Version number of this provider */
        "fips",         /* FIPS supporting provider */
        "engine",       /* An old style engine masquerading as a provider */
    };
    size_t i;

    for (i = 0; i < OSSL_NELEM(predefined_names); i++)
        if (ossl_property_name(ctx, predefined_names[i], 1) == 0)
            goto err;

    /* Pre-populate the two Boolean values */
    if ((ossl_property_true = ossl_property_value(ctx, "yes", 1)) == 0
        || (ossl_property_false = ossl_property_value(ctx, "no", 1)) == 0)
        goto err;

    return 1;
err:
    return 0;
}