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
struct jsonsl_state_st {int level; scalar_t__ type; scalar_t__ nelem; } ;
typedef  TYPE_1__* jsonsl_t ;
typedef  int /*<<< orphan*/ * jsonsl_jpr_t ;
typedef  scalar_t__ jsonsl_jpr_match_t ;
struct TYPE_3__ {size_t* jpr_root; int jpr_count; int /*<<< orphan*/ ** jprs; struct jsonsl_state_st* stack; } ;

/* Variables and functions */
 scalar_t__ JSONSL_MATCH_COMPLETE ; 
 scalar_t__ JSONSL_MATCH_NOMATCH ; 
 scalar_t__ JSONSL_MATCH_POSSIBLE ; 
 scalar_t__ JSONSL_T_LIST ; 
 scalar_t__ jsonsl_jpr_match (int /*<<< orphan*/ *,scalar_t__,int,char const*,size_t) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 

jsonsl_jpr_t jsonsl_jpr_match_state(jsonsl_t jsn,
                                    struct jsonsl_state_st *state,
                                    const char *key,
                                    size_t nkey,
                                    jsonsl_jpr_match_t *out)
{
    struct jsonsl_state_st *parent_state;
    jsonsl_jpr_t ret = NULL;

    /* Jump and JPR tables for our own state and the parent state */
    size_t *jmptable, *pjmptable;
    size_t jmp_cur, ii, ourjmpidx;

    if (!jsn->jpr_root) {
        *out = JSONSL_MATCH_NOMATCH;
        return NULL;
    }

    pjmptable = jsn->jpr_root + (jsn->jpr_count * (state->level-1));
    jmptable = pjmptable + jsn->jpr_count;

    /* If the parent cannot match, then invalidate it */
    if (*pjmptable == 0) {
        *jmptable = 0;
        *out = JSONSL_MATCH_NOMATCH;
        return NULL;
    }

    parent_state = jsn->stack + state->level - 1;

    if (parent_state->type == JSONSL_T_LIST) {
        nkey = (size_t) parent_state->nelem;
    }

    *jmptable = 0;
    ourjmpidx = 0;
    memset(jmptable, 0, sizeof(int) * jsn->jpr_count);

    for (ii = 0; ii <  jsn->jpr_count; ii++) {
        jmp_cur = pjmptable[ii];
        if (jmp_cur) {
            jsonsl_jpr_t jpr = jsn->jprs[jmp_cur-1];
            *out = jsonsl_jpr_match(jpr,
                                    parent_state->type,
                                    parent_state->level,
                                    key, nkey);
            if (*out == JSONSL_MATCH_COMPLETE) {
                ret = jpr;
                *jmptable = 0;
                return ret;
            } else if (*out == JSONSL_MATCH_POSSIBLE) {
                jmptable[ourjmpidx] = ii+1;
                ourjmpidx++;
            }
        } else {
            break;
        }
    }
    if (!*jmptable) {
        *out = JSONSL_MATCH_NOMATCH;
    }
    return NULL;
}