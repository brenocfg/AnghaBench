#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* cfg; } ;
typedef  TYPE_2__ lfs2_t ;
struct TYPE_8__ {int /*<<< orphan*/  block; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_3__ lfs2_cache_t ;
struct TYPE_6__ {int /*<<< orphan*/  cache_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  LFS2_BLOCK_NULL ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void lfs2_cache_zero(lfs2_t *lfs2, lfs2_cache_t *pcache) {
    // zero to avoid information leak
    memset(pcache->buffer, 0xff, lfs2->cfg->cache_size);
    pcache->block = LFS2_BLOCK_NULL;
}