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
typedef  scalar_t__ const uint8_t ;
typedef  int /*<<< orphan*/  lfs2_t ;
typedef  size_t lfs2_size_t ;
typedef  size_t lfs2_off_t ;
typedef  int /*<<< orphan*/  lfs2_cache_t ;
typedef  int /*<<< orphan*/  lfs2_block_t ;

/* Variables and functions */
 int LFS2_CMP_EQ ; 
 int LFS2_CMP_GT ; 
 int LFS2_CMP_LT ; 
 int lfs2_bd_read (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,size_t,scalar_t__ const*,int) ; 

__attribute__((used)) static int lfs2_bd_cmp(lfs2_t *lfs2,
        const lfs2_cache_t *pcache, lfs2_cache_t *rcache, lfs2_size_t hint,
        lfs2_block_t block, lfs2_off_t off,
        const void *buffer, lfs2_size_t size) {
    const uint8_t *data = buffer;

    for (lfs2_off_t i = 0; i < size; i++) {
        uint8_t dat;
        int err = lfs2_bd_read(lfs2,
                pcache, rcache, hint-i,
                block, off+i, &dat, 1);
        if (err) {
            return err;
        }

        if (dat != data[i]) {
            return (dat < data[i]) ? LFS2_CMP_LT : LFS2_CMP_GT;
        }
    }

    return LFS2_CMP_EQ;
}