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
struct jsonsl_jpr_component_st {scalar_t__ ptype; } ;
typedef  TYPE_1__* jsonsl_jpr_t ;
typedef  int /*<<< orphan*/  jsonsl_jpr_match_t ;
struct TYPE_3__ {int ncomponents; scalar_t__ match_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  JSONSL_MATCH_COMPLETE ; 
 int /*<<< orphan*/  JSONSL_MATCH_POSSIBLE ; 
 int /*<<< orphan*/  JSONSL_MATCH_TYPE_MISMATCH ; 
 scalar_t__ JSONSL_PATH_NUMERIC ; 
 unsigned int JSONSL_T_LIST ; 
 unsigned int JSONSL_T_OBJECT ; 

__attribute__((used)) static jsonsl_jpr_match_t
jsonsl__match_continue(jsonsl_jpr_t jpr,
                       const struct jsonsl_jpr_component_st *component,
                       unsigned prlevel, unsigned chtype)
{
    const struct jsonsl_jpr_component_st *next_comp = component + 1;
    if (prlevel == jpr->ncomponents - 1) {
        /* This is the match. Check the expected type of the match against
         * the child */
        if (jpr->match_type == 0 || jpr->match_type == chtype) {
            return JSONSL_MATCH_COMPLETE;
        } else {
            return JSONSL_MATCH_TYPE_MISMATCH;
        }
    }
    if (chtype == JSONSL_T_LIST) {
        if (next_comp->ptype == JSONSL_PATH_NUMERIC) {
            return JSONSL_MATCH_POSSIBLE;
        } else {
            return JSONSL_MATCH_TYPE_MISMATCH;
        }
    } else if (chtype == JSONSL_T_OBJECT) {
        if (next_comp->ptype == JSONSL_PATH_NUMERIC) {
            return JSONSL_MATCH_TYPE_MISMATCH;
        } else {
            return JSONSL_MATCH_POSSIBLE;
        }
    } else {
        return JSONSL_MATCH_TYPE_MISMATCH;
    }
}