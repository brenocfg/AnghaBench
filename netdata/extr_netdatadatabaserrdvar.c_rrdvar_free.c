#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  avl_tree_lock ;
struct TYPE_10__ {char* hostname; } ;
struct TYPE_9__ {int options; struct TYPE_9__* name; struct TYPE_9__* value; } ;
typedef  TYPE_1__ RRDVAR ;
typedef  TYPE_2__ RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  D_VARIABLES ; 
 int RRDVAR_OPTION_ALLOCATED ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  error (char*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  freez (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdvar_index_del (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

inline void rrdvar_free(RRDHOST *host, avl_tree_lock *tree, RRDVAR *rv) {
    (void)host;

    if(!rv) return;

    if(tree) {
        debug(D_VARIABLES, "Deleting variable '%s'", rv->name);
        if(unlikely(!rrdvar_index_del(tree, rv)))
            error("RRDVAR: Attempted to delete variable '%s' from host '%s', but it is not found.", rv->name, host->hostname);
    }

    if(rv->options & RRDVAR_OPTION_ALLOCATED)
        freez(rv->value);

    freez(rv->name);
    freez(rv);
}