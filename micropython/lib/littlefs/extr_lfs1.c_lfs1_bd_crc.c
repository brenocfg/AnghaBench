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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  rcache; } ;
typedef  TYPE_1__ lfs1_t ;
typedef  int /*<<< orphan*/  lfs1_size_t ;
typedef  int /*<<< orphan*/  lfs1_off_t ;
typedef  int /*<<< orphan*/  lfs1_block_t ;

/* Variables and functions */
 int lfs1_cache_crc (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lfs1_bd_crc(lfs1_t *lfs1, lfs1_block_t block,
        lfs1_off_t off, lfs1_size_t size, uint32_t *crc) {
    return lfs1_cache_crc(lfs1, &lfs1->rcache, NULL, block, off, size, crc);
}