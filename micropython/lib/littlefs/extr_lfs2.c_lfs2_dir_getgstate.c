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
typedef  int /*<<< orphan*/  temp ;
struct lfs2_gstate {int dummy; } ;
typedef  int /*<<< orphan*/  lfs2_t ;
typedef  scalar_t__ lfs2_stag_t ;
typedef  int /*<<< orphan*/  lfs2_mdir_t ;

/* Variables and functions */
 scalar_t__ LFS2_ERR_NOENT ; 
 int /*<<< orphan*/  LFS2_MKTAG (int,int /*<<< orphan*/ ,int) ; 
 int LFS2_TYPE_MOVESTATE ; 
 scalar_t__ lfs2_dir_get (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lfs2_gstate*) ; 
 int /*<<< orphan*/  lfs2_gstate_fromle32 (struct lfs2_gstate*) ; 
 int /*<<< orphan*/  lfs2_gstate_xor (struct lfs2_gstate*,struct lfs2_gstate*) ; 

__attribute__((used)) static int lfs2_dir_getgstate(lfs2_t *lfs2, const lfs2_mdir_t *dir,
        struct lfs2_gstate *gstate) {
    struct lfs2_gstate temp;
    lfs2_stag_t res = lfs2_dir_get(lfs2, dir, LFS2_MKTAG(0x7ff, 0, 0),
            LFS2_MKTAG(LFS2_TYPE_MOVESTATE, 0, sizeof(temp)), &temp);
    if (res < 0 && res != LFS2_ERR_NOENT) {
        return res;
    }

    if (res != LFS2_ERR_NOENT) {
        // xor together to find resulting gstate
        lfs2_gstate_fromle32(&temp);
        lfs2_gstate_xor(gstate, &temp);
    }

    return 0;
}