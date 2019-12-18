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
struct TYPE_4__ {int /*<<< orphan*/  rcache; } ;
typedef  TYPE_1__ lfs1_t ;
typedef  int /*<<< orphan*/  lfs1_size_t ;
typedef  int /*<<< orphan*/  lfs1_off_t ;
typedef  int /*<<< orphan*/  lfs1_block_t ;

/* Variables and functions */
 int lfs1_cache_read (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lfs1_bd_read(lfs1_t *lfs1, lfs1_block_t block,
        lfs1_off_t off, void *buffer, lfs1_size_t size) {
    // if we ever do more than writes to alternating pairs,
    // this may need to consider pcache
    return lfs1_cache_read(lfs1, &lfs1->rcache, NULL,
            block, off, buffer, size);
}