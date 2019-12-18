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
typedef  int /*<<< orphan*/  uint8_t ;
struct lfs2_commit {int /*<<< orphan*/  off; int /*<<< orphan*/  crc; int /*<<< orphan*/  block; } ;
struct TYPE_4__ {int /*<<< orphan*/  rcache; int /*<<< orphan*/  pcache; } ;
typedef  TYPE_1__ lfs2_t ;
typedef  scalar_t__ lfs2_size_t ;

/* Variables and functions */
 int lfs2_bd_prog (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  lfs2_crc (int /*<<< orphan*/ ,void const*,scalar_t__) ; 

__attribute__((used)) static int lfs2_dir_commitprog(lfs2_t *lfs2, struct lfs2_commit *commit,
        const void *buffer, lfs2_size_t size) {
    int err = lfs2_bd_prog(lfs2,
            &lfs2->pcache, &lfs2->rcache, false,
            commit->block, commit->off ,
            (const uint8_t*)buffer, size);
    if (err) {
        return err;
    }

    commit->crc = lfs2_crc(commit->crc, buffer, size);
    commit->off += size;
    return 0;
}