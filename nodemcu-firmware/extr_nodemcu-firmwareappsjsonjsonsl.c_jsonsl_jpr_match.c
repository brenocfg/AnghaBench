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
struct jsonsl_jpr_component_st {scalar_t__ ptype; size_t idx; size_t len; int /*<<< orphan*/  pstr; scalar_t__ is_arridx; } ;
typedef  TYPE_1__* jsonsl_jpr_t ;
typedef  int /*<<< orphan*/  jsonsl_jpr_match_t ;
struct TYPE_3__ {unsigned int ncomponents; struct jsonsl_jpr_component_st* components; } ;

/* Variables and functions */
 int /*<<< orphan*/  JSONSL_MATCH_COMPLETE ; 
 int /*<<< orphan*/  JSONSL_MATCH_NOMATCH ; 
 int /*<<< orphan*/  JSONSL_MATCH_POSSIBLE ; 
 int /*<<< orphan*/  JSONSL_MATCH_TYPE_MISMATCH ; 
 scalar_t__ JSONSL_PATH_NUMERIC ; 
 scalar_t__ JSONSL_PATH_WILDCARD ; 
 unsigned int JSONSL_T_LIST ; 
 int strncmp (int /*<<< orphan*/ ,char const*,size_t) ; 

jsonsl_jpr_match_t
jsonsl_jpr_match(jsonsl_jpr_t jpr,
                   unsigned int parent_type,
                   unsigned int parent_level,
                   const char *key,
                   size_t nkey)
{
    /* find our current component. This is the child level */
    int cmpret;
    struct jsonsl_jpr_component_st *p_component;
    p_component = jpr->components + parent_level;

    if (parent_level >= jpr->ncomponents) {
        return JSONSL_MATCH_NOMATCH;
    }

    /* Lone query for 'root' element. Always matches */
    if (parent_level == 0) {
        if (jpr->ncomponents == 1) {
            return JSONSL_MATCH_COMPLETE;
        } else {
            return JSONSL_MATCH_POSSIBLE;
        }
    }

    /* Wildcard, always matches */
    if (p_component->ptype == JSONSL_PATH_WILDCARD) {
        if (parent_level == jpr->ncomponents-1) {
            return JSONSL_MATCH_COMPLETE;
        } else {
            return JSONSL_MATCH_POSSIBLE;
        }
    }

    /* Check numeric array index. This gets its special block so we can avoid
     * string comparisons */
    if (p_component->ptype == JSONSL_PATH_NUMERIC) {
        if (parent_type == JSONSL_T_LIST) {
            if (p_component->idx != nkey) {
                /* Wrong index */
                return JSONSL_MATCH_NOMATCH;
            } else {
                if (parent_level == jpr->ncomponents-1) {
                    /* This is the last element of the path */
                    return JSONSL_MATCH_COMPLETE;
                } else {
                    /* Intermediate element */
                    return JSONSL_MATCH_POSSIBLE;
                }
            }
        } else if (p_component->is_arridx) {
            /* Numeric and an array index (set explicitly by user). But not
             * a list for a parent */
            return JSONSL_MATCH_TYPE_MISMATCH;
        }
    } else if (parent_type == JSONSL_T_LIST) {
        return JSONSL_MATCH_TYPE_MISMATCH;
    }

    /* Check lengths */
    if (p_component->len != nkey) {
        return JSONSL_MATCH_NOMATCH;
    }

    /* Check string comparison */
    cmpret = strncmp(p_component->pstr, key, nkey);
    if (cmpret == 0) {
        if (parent_level == jpr->ncomponents-1) {
            return JSONSL_MATCH_COMPLETE;
        } else {
            return JSONSL_MATCH_POSSIBLE;
        }
    }

    return JSONSL_MATCH_NOMATCH;
}