#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* cfg; } ;
typedef  TYPE_1__ lfs1_t ;
struct TYPE_12__ {int block; int /*<<< orphan*/  buffer; int /*<<< orphan*/  off; } ;
typedef  TYPE_2__ lfs1_cache_t ;
struct TYPE_13__ {int (* prog ) (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  prog_size; } ;

/* Variables and functions */
 int LFS1_ERR_CORRUPT ; 
 int lfs1_cache_cmp (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lfs1_cache_zero (TYPE_1__*,TYPE_2__*) ; 
 int stub1 (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lfs1_cache_flush(lfs1_t *lfs1,
        lfs1_cache_t *pcache, lfs1_cache_t *rcache) {
    if (pcache->block != 0xffffffff) {
        int err = lfs1->cfg->prog(lfs1->cfg, pcache->block,
                pcache->off, pcache->buffer, lfs1->cfg->prog_size);
        if (err) {
            return err;
        }

        if (rcache) {
            int res = lfs1_cache_cmp(lfs1, rcache, NULL, pcache->block,
                    pcache->off, pcache->buffer, lfs1->cfg->prog_size);
            if (res < 0) {
                return res;
            }

            if (!res) {
                return LFS1_ERR_CORRUPT;
            }
        }

        lfs1_cache_zero(lfs1, pcache);
    }

    return 0;
}