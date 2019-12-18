#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* cfg; int /*<<< orphan*/  pcache; int /*<<< orphan*/  rcache; } ;
typedef  TYPE_1__ lfs1_t ;
struct TYPE_7__ {int (* sync ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  lfs1_cache_drop (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int lfs1_cache_flush (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*) ; 

__attribute__((used)) static int lfs1_bd_sync(lfs1_t *lfs1) {
    lfs1_cache_drop(lfs1, &lfs1->rcache);

    int err = lfs1_cache_flush(lfs1, &lfs1->pcache, NULL);
    if (err) {
        return err;
    }

    return lfs1->cfg->sync(lfs1->cfg);
}