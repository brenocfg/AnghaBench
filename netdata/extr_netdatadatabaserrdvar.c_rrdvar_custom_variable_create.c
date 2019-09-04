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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  char calculated_number ;
typedef  int /*<<< orphan*/  avl_tree_lock ;
typedef  int /*<<< orphan*/  RRDVAR ;

/* Variables and functions */
 int /*<<< orphan*/  D_VARIABLES ; 
 char NAN ; 
 int RRDVAR_OPTION_ALLOCATED ; 
 int RRDVAR_OPTION_CUSTOM_HOST_VAR ; 
 int /*<<< orphan*/  RRDVAR_TYPE_CALCULATED ; 
 char* callocz (int,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  freez (char*) ; 
 int /*<<< orphan*/ * rrdvar_create_and_index (char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  rrdvar_fix_name (char*) ; 
 int /*<<< orphan*/ * rrdvar_index_find (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_hash (char*) ; 
 char* strdupz (char const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static RRDVAR *rrdvar_custom_variable_create(const char *scope, avl_tree_lock *tree_lock, const char *name) {
    calculated_number *v = callocz(1, sizeof(calculated_number));
    *v = NAN;

    RRDVAR *rv = rrdvar_create_and_index(scope, tree_lock, name, RRDVAR_TYPE_CALCULATED, RRDVAR_OPTION_CUSTOM_HOST_VAR|RRDVAR_OPTION_ALLOCATED, v);
    if(unlikely(!rv)) {
        freez(v);
        debug(D_VARIABLES, "Requested variable '%s' already exists - possibly 2 plugins are updating it at the same time.", name);

        char *variable = strdupz(name);
        rrdvar_fix_name(variable);
        uint32_t hash = simple_hash(variable);

        // find the existing one to return it
        rv = rrdvar_index_find(tree_lock, variable, hash);

        freez(variable);
    }

    return rv;
}