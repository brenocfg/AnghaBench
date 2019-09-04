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
 int /*<<< orphan*/  PROPERTY_TYPE_STRING ; 
 int /*<<< orphan*/  PROP_F_PARSE_STRING ; 
 int /*<<< orphan*/  PROP_R_NO_MATCHING_STRING_DELIMETER ; 
 int /*<<< orphan*/  PROP_R_STRING_TOO_LONG ; 
 int /*<<< orphan*/  PROPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_property_value (int /*<<< orphan*/ *,char*,int const) ; 
 char* skip_space (char const*) ; 

__attribute__((used)) static int parse_string(OPENSSL_CTX *ctx, const char *t[], char delim,
                        PROPERTY_DEFINITION *res, const int create)
{
    char v[1000];
    const char *s = *t;
    size_t i = 0;
    int err = 0;

    while (*s != '\0' && *s != delim) {
        if (i < sizeof(v) - 1)
            v[i++] = *s;
        else
            err = 1;
        s++;
    }
    if (*s == '\0') {
        PROPerr(PROP_F_PARSE_STRING,
                PROP_R_NO_MATCHING_STRING_DELIMETER);
        return 0;
    }
    v[i] = '\0';
    *t = skip_space(s + 1);
    if (err)
        PROPerr(PROP_F_PARSE_STRING, PROP_R_STRING_TOO_LONG);
    else
        res->v.str_val = ossl_property_value(ctx, v, create);
    res->type = PROPERTY_TYPE_STRING;
    return !err;
}