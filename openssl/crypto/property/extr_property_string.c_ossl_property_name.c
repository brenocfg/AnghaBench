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
struct TYPE_3__ {int /*<<< orphan*/  prop_name_idx; int /*<<< orphan*/  prop_names; } ;
typedef  TYPE_1__ PROPERTY_STRING_DATA ;
typedef  int /*<<< orphan*/  OSSL_PROPERTY_IDX ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_CTX_PROPERTY_STRING_INDEX ; 
 TYPE_1__* openssl_ctx_get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_property_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  property_string_data_method ; 

OSSL_PROPERTY_IDX ossl_property_name(OPENSSL_CTX *ctx, const char *s,
                                     int create)
{
    PROPERTY_STRING_DATA *propdata
        = openssl_ctx_get_data(ctx, OPENSSL_CTX_PROPERTY_STRING_INDEX,
                               &property_string_data_method);

    if (propdata == NULL)
        return 0;
    return ossl_property_string(propdata->prop_names,
                                create ? &propdata->prop_name_idx : NULL,
                                s);
}