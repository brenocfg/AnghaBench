#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* search_name; } ;
struct TYPE_6__ {TYPE_1__ dir; } ;
struct TYPE_7__ {scalar_t__ expected_type; TYPE_2__ _; } ;
typedef  TYPE_3__ OSSL_STORE_LOADER_CTX ;

/* Variables and functions */
 scalar_t__ OSSL_STORE_INFO_CERT ; 
 scalar_t__ OSSL_STORE_INFO_CRL ; 
 scalar_t__ ossl_isdigit (char const) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static int file_name_check(OSSL_STORE_LOADER_CTX *ctx, const char *name)
{
    const char *p = NULL;

    /* If there are no search criteria, all names are accepted */
    if (ctx->_.dir.search_name[0] == '\0')
        return 1;

    /* If the expected type isn't supported, no name is accepted */
    if (ctx->expected_type != 0
        && ctx->expected_type != OSSL_STORE_INFO_CERT
        && ctx->expected_type != OSSL_STORE_INFO_CRL)
        return 0;

    /*
     * First, check the basename
     */
    if (strncasecmp(name, ctx->_.dir.search_name,
                    sizeof(ctx->_.dir.search_name) - 1) != 0
        || name[sizeof(ctx->_.dir.search_name) - 1] != '.')
        return 0;
    p = &name[sizeof(ctx->_.dir.search_name)];

    /*
     * Then, if the expected type is a CRL, check that the extension starts
     * with 'r'
     */
    if (*p == 'r') {
        p++;
        if (ctx->expected_type != 0
            && ctx->expected_type != OSSL_STORE_INFO_CRL)
            return 0;
    } else if (ctx->expected_type == OSSL_STORE_INFO_CRL) {
        return 0;
    }

    /*
     * Last, check that the rest of the extension is a decimal number, at
     * least one digit long.
     */
    if (!ossl_isdigit(*p))
        return 0;
    while (ossl_isdigit(*p))
        p++;

# ifdef __VMS
    /*
     * One extra step here, check for a possible generation number.
     */
    if (*p == ';')
        for (p++; *p != '\0'; p++)
            if (!ossl_isdigit(*p))
                break;
# endif

    /*
     * If we've reached the end of the string at this point, we've successfully
     * found a fitting file name.
     */
    return *p == '\0';
}