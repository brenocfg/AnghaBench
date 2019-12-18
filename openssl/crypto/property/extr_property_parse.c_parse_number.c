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
typedef  int int64_t ;
struct TYPE_4__ {int int_val; } ;
struct TYPE_5__ {TYPE_1__ v; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ PROPERTY_DEFINITION ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROP ; 
 int /*<<< orphan*/  ERR_raise_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  PROPERTY_TYPE_NUMBER ; 
 int /*<<< orphan*/  PROP_R_NOT_A_DECIMAL_DIGIT ; 
 scalar_t__ ossl_isdigit (char const) ; 
 int /*<<< orphan*/  ossl_isspace (char const) ; 
 char* skip_space (char const*) ; 

__attribute__((used)) static int parse_number(const char *t[], PROPERTY_DEFINITION *res)
{
    const char *s = *t;
    int64_t v = 0;

    if (!ossl_isdigit(*s))
        return 0;
    do {
        v = v * 10 + (*s++ - '0');
    } while (ossl_isdigit(*s));
    if (!ossl_isspace(*s) && *s != '\0' && *s != ',') {
        ERR_raise_data(ERR_LIB_PROP, PROP_R_NOT_A_DECIMAL_DIGIT,
                       "HERE-->%s", *t);
        return 0;
    }
    *t = skip_space(s);
    res->type = PROPERTY_TYPE_NUMBER;
    res->v.int_val = v;
    return 1;
}