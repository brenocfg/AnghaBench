#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct jsonsl_state_st {scalar_t__ type; int level; int nelem; } ;
typedef  struct jsonsl_jpr_component_st {size_t len; int idx; int /*<<< orphan*/  pstr; } const jsonsl_jpr_component_st ;
typedef  TYPE_1__* jsonsl_jpr_t ;
typedef  int /*<<< orphan*/  jsonsl_jpr_match_t ;
struct TYPE_4__ {struct jsonsl_jpr_component_st const* components; } ;

/* Variables and functions */
 int /*<<< orphan*/  JSONSL_MATCH_NOMATCH ; 
 scalar_t__ JSONSL_T_OBJECT ; 
 int /*<<< orphan*/  jsonsl__match_continue (TYPE_1__*,struct jsonsl_jpr_component_st const*,int,scalar_t__) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 

jsonsl_jpr_match_t
jsonsl_path_match(jsonsl_jpr_t jpr,
                  const struct jsonsl_state_st *parent,
                  const struct jsonsl_state_st *child,
                  const char *key, size_t nkey)
{
    const struct jsonsl_jpr_component_st *comp;
    if (!parent) {
        /* No parent. Return immediately since it's always a match */
        return jsonsl__match_continue(jpr, jpr->components, 0, child->type);
    }

    comp = jpr->components + parent->level;

    /* note that we don't need to verify the type of the match, this is
     * always done through the previous call to jsonsl__match_continue.
     * If we are in a POSSIBLE tree then we can be certain the types (at
     * least at this level) are correct */
    if (parent->type == JSONSL_T_OBJECT) {
        if (comp->len != nkey || strncmp(key, comp->pstr, nkey) != 0) {
            return JSONSL_MATCH_NOMATCH;
        }
    } else {
        if (comp->idx != parent->nelem - 1) {
            return JSONSL_MATCH_NOMATCH;
        }
    }
    return jsonsl__match_continue(jpr, comp, parent->level, child->type);
}