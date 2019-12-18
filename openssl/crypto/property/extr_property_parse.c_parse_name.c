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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  OSSL_PROPERTY_IDX ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROP ; 
 int /*<<< orphan*/  ERR_raise_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  PROP_R_NAME_TOO_LONG ; 
 int /*<<< orphan*/  PROP_R_NOT_AN_IDENTIFIER ; 
 scalar_t__ ossl_isalnum (char const) ; 
 int /*<<< orphan*/  ossl_isalpha (char const) ; 
 int /*<<< orphan*/  ossl_property_name (int /*<<< orphan*/ *,char*,int) ; 
 char ossl_tolower (char const) ; 
 char* skip_space (char const*) ; 

__attribute__((used)) static int parse_name(OPENSSL_CTX *ctx, const char *t[], int create,
                      OSSL_PROPERTY_IDX *idx)
{
    char name[100];
    int err = 0;
    size_t i = 0;
    const char *s = *t;
    int user_name = 0;

    for (;;) {
        if (!ossl_isalpha(*s)) {
            ERR_raise_data(ERR_LIB_PROP, PROP_R_NOT_AN_IDENTIFIER,
                           "HERE-->%s", *t);
            return 0;
        }
        do {
            if (i < sizeof(name) - 1)
                name[i++] = ossl_tolower(*s);
            else
                err = 1;
        } while (*++s == '_' || ossl_isalnum(*s));
        if (*s != '.')
            break;
        user_name = 1;
        if (i < sizeof(name) - 1)
            name[i++] = *s;
        else
            err = 1;
        s++;
    }
    name[i] = '\0';
    if (err) {
        ERR_raise_data(ERR_LIB_PROP, PROP_R_NAME_TOO_LONG, "HERE-->%s", *t);
        return 0;
    }
    *t = skip_space(s);
    *idx = ossl_property_name(ctx, name, user_name && create);
    return 1;
}