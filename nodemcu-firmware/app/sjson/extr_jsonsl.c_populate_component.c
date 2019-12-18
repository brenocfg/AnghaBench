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
struct jsonsl_jpr_component_st {char* pstr; void* len; scalar_t__ ptype; void* idx; } ;
typedef  scalar_t__ jsonsl_jpr_type_t ;
typedef  int /*<<< orphan*/  jsonsl_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  JSONSL_ERROR_PERCENT_BADHEX ; 
 scalar_t__ JSONSL_PATH_INVALID ; 
 scalar_t__ JSONSL_PATH_NONE ; 
 scalar_t__ JSONSL_PATH_NUMERIC ; 
 scalar_t__ JSONSL_PATH_STRING ; 
 scalar_t__ JSONSL_PATH_WILDCARD ; 
 char JSONSL_PATH_WILDCARD_CHAR ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ isxdigit (char) ; 
 void* strlen (char*) ; 
 char* strstr (char*,char*) ; 
 void* strtoul (char*,char**,int) ; 

__attribute__((used)) static
jsonsl_jpr_type_t
populate_component(char *in,
                   struct jsonsl_jpr_component_st *component,
                   char **next,
                   jsonsl_error_t *errp)
{
    unsigned long pctval;
    char *c = NULL, *outp = NULL, *end = NULL;
    size_t input_len;
    jsonsl_jpr_type_t ret = JSONSL_PATH_NONE;

    if (*next == NULL || *(*next) == '\0') {
        return JSONSL_PATH_NONE;
    }

    /* Replace the next / with a NULL */
    *next = strstr(in, "/");
    if (*next != NULL) {
        *(*next) = '\0'; /* drop the forward slash */
        input_len = *next - in;
        end = *next;
        *next += 1; /* next character after the '/' */
    } else {
        input_len = strlen(in);
        end = in + input_len + 1;
    }

    component->pstr = in;

    /* Check for special components of interest */
    if (*in == JSONSL_PATH_WILDCARD_CHAR && input_len == 1) {
        /* Lone wildcard */
        ret = JSONSL_PATH_WILDCARD;
        goto GT_RET;
    } else if (isdigit(*in)) {
        /* ASCII Numeric */
        char *endptr;
        component->idx = strtoul(in, &endptr, 10);
        if (endptr && *endptr == '\0') {
            ret = JSONSL_PATH_NUMERIC;
            goto GT_RET;
        }
    }

    /* Default, it's a string */
    ret = JSONSL_PATH_STRING;
    for (c = outp = in; c < end; c++, outp++) {
        char origc;
        if (*c != '%') {
            goto GT_ASSIGN;
        }
        /*
         * c = { [+0] = '%', [+1] = 'b', [+2] = 'e', [+3] = '\0' }
         */

        /* Need %XX */
        if (c+2 >= end) {
            *errp = JSONSL_ERROR_PERCENT_BADHEX;
            return JSONSL_PATH_INVALID;
        }
        if (! (isxdigit(*(c+1)) && isxdigit(*(c+2))) ) {
            *errp = JSONSL_ERROR_PERCENT_BADHEX;
            return JSONSL_PATH_INVALID;
        }

        /* Temporarily null-terminate the characters */
        origc = *(c+3);
        *(c+3) = '\0';
        pctval = strtoul(c+1, NULL, 16);
        *(c+3) = origc;

        *outp = (char) pctval;
        c += 2;
        continue;

        GT_ASSIGN:
        *outp = *c;
    }
    /* Null-terminate the string */
    for (; outp < c; outp++) {
        *outp = '\0';
    }

    GT_RET:
    component->ptype = ret;
    if (ret != JSONSL_PATH_WILDCARD) {
        component->len = strlen(component->pstr);
    }
    return ret;
}