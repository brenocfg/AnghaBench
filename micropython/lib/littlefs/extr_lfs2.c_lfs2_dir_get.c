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
typedef  int /*<<< orphan*/  lfs2_tag_t ;
typedef  int /*<<< orphan*/  lfs2_t ;
typedef  int /*<<< orphan*/  lfs2_stag_t ;
typedef  int /*<<< orphan*/  lfs2_mdir_t ;

/* Variables and functions */
 int /*<<< orphan*/  lfs2_dir_getslice (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lfs2_tag_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static lfs2_stag_t lfs2_dir_get(lfs2_t *lfs2, const lfs2_mdir_t *dir,
        lfs2_tag_t gmask, lfs2_tag_t gtag, void *buffer) {
    return lfs2_dir_getslice(lfs2, dir,
            gmask, gtag,
            0, buffer, lfs2_tag_size(gtag));
}