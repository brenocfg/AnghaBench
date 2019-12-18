#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v ;
struct TYPE_4__ {int /*<<< orphan*/  str_val; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; TYPE_1__ v; } ;
typedef  TYPE_2__ PROPERTY_DEFINITION ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROP ; 
 int /*<<< orphan*/  ERR_raise_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  PROPERTY_TYPE_STRING ; 
 int /*<<< orphan*/  PROP_R_NOT_AN_ASCII_CHARACTER ; 
 int /*<<< orphan*/  PROP_R_STRING_TOO_LONG ; 
 scalar_t__ ossl_isprint (char const) ; 
 int /*<<< orphan*/  ossl_isspace (char const) ; 
 int /*<<< orphan*/  ossl_property_value (int /*<<< orphan*/ *,char*,int const) ; 
 char ossl_tolower (char const) ; 
 char* skip_space (char const*) ; 

__attribute__((used)) static int parse_unquoted(OPENSSL_CTX *ctx, const char *t[],
                          PROPERTY_DEFINITION *res, const int create)
{
    char v[1000];
    const char *s = *t;
    size_t i = 0;
    int err = 0;

    if (*s == '\0' || *s == ',')
        return 0;
    while (ossl_isprint(*s) && !ossl_isspace(*s) && *s != ',') {
        if (i < sizeof(v) - 1)
            v[i++] = ossl_tolower(*s);
        else
            err = 1;
        s++;
    }
    if (!ossl_isspace(*s) && *s != '\0' && *s != ',') {
        ERR_raise_data(ERR_LIB_PROP, PROP_R_NOT_AN_ASCII_CHARACTER,
                       "HERE-->%s", s);
        return 0;
    }
    v[i] = 0;
    if (err) {
        ERR_raise_data(ERR_LIB_PROP, PROP_R_STRING_TOO_LONG, "HERE-->%s", *t);
    } else {
        res->v.str_val = ossl_property_value(ctx, v, create);
    }
    *t = skip_space(s);
    res->type = PROPERTY_TYPE_STRING;
    return !err;
}