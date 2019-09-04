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
typedef  int /*<<< orphan*/  avl_tree_lock ;
typedef  int /*<<< orphan*/  avl ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ RRDVAR ;

/* Variables and functions */
 int /*<<< orphan*/  D_VARIABLES ; 
 scalar_t__ avl_insert_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline RRDVAR *rrdvar_index_add(avl_tree_lock *tree, RRDVAR *rv) {
    RRDVAR *ret = (RRDVAR *)avl_insert_lock(tree, (avl *)(rv));
    if(ret != rv)
        debug(D_VARIABLES, "Request to insert RRDVAR '%s' into index failed. Already exists.", rv->name);

    return ret;
}