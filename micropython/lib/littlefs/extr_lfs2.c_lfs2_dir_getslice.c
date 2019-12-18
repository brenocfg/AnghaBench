#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tag ;
typedef  int /*<<< orphan*/  ntag ;
typedef  int lfs2_tag_t ;
struct TYPE_9__ {int tag; } ;
struct TYPE_7__ {int /*<<< orphan*/  rcache; TYPE_3__ gstate; } ;
typedef  TYPE_1__ lfs2_t ;
typedef  int lfs2_stag_t ;
typedef  int lfs2_size_t ;
typedef  scalar_t__ lfs2_off_t ;
struct TYPE_8__ {scalar_t__ off; int etag; int /*<<< orphan*/ * pair; } ;
typedef  TYPE_2__ lfs2_mdir_t ;

/* Variables and functions */
 int LFS2_ERR_NOENT ; 
 int LFS2_MKTAG (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LFS2_TYPE_CREATE ; 
 scalar_t__ LFS2_TYPE_SPLICE ; 
 int lfs2_bd_read (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,void*,int) ; 
 int lfs2_frombe32 (int) ; 
 scalar_t__ lfs2_gstate_hasmovehere (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int lfs2_min (int /*<<< orphan*/ ,int) ; 
 scalar_t__ lfs2_tag_dsize (int) ; 
 scalar_t__ lfs2_tag_id (int) ; 
 scalar_t__ lfs2_tag_isdelete (int) ; 
 int /*<<< orphan*/  lfs2_tag_size (int) ; 
 int lfs2_tag_splice (int) ; 
 scalar_t__ lfs2_tag_type1 (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static lfs2_stag_t lfs2_dir_getslice(lfs2_t *lfs2, const lfs2_mdir_t *dir,
        lfs2_tag_t gmask, lfs2_tag_t gtag,
        lfs2_off_t goff, void *gbuffer, lfs2_size_t gsize) {
    lfs2_off_t off = dir->off;
    lfs2_tag_t ntag = dir->etag;
    lfs2_stag_t gdiff = 0;

    if (lfs2_gstate_hasmovehere(&lfs2->gstate, dir->pair) &&
            lfs2_tag_id(gtag) <= lfs2_tag_id(lfs2->gstate.tag)) {
        // synthetic moves
        gdiff -= LFS2_MKTAG(0, 1, 0);
    }

    // iterate over dir block backwards (for faster lookups)
    while (off >= sizeof(lfs2_tag_t) + lfs2_tag_dsize(ntag)) {
        off -= lfs2_tag_dsize(ntag);
        lfs2_tag_t tag = ntag;
        int err = lfs2_bd_read(lfs2,
                NULL, &lfs2->rcache, sizeof(ntag),
                dir->pair[0], off, &ntag, sizeof(ntag));
        if (err) {
            return err;
        }

        ntag = (lfs2_frombe32(ntag) ^ tag) & 0x7fffffff;

        if (lfs2_tag_id(gmask) != 0 &&
                lfs2_tag_type1(tag) == LFS2_TYPE_SPLICE &&
                lfs2_tag_id(tag) <= lfs2_tag_id(gtag - gdiff)) {
            if (tag == (LFS2_MKTAG(LFS2_TYPE_CREATE, 0, 0) |
                    (LFS2_MKTAG(0, 0x3ff, 0) & (gtag - gdiff)))) {
                // found where we were created
                return LFS2_ERR_NOENT;
            }

            // move around splices
            gdiff += LFS2_MKTAG(0, lfs2_tag_splice(tag), 0);
        }

        if ((gmask & tag) == (gmask & (gtag - gdiff))) {
            if (lfs2_tag_isdelete(tag)) {
                return LFS2_ERR_NOENT;
            }

            lfs2_size_t diff = lfs2_min(lfs2_tag_size(tag), gsize);
            err = lfs2_bd_read(lfs2,
                    NULL, &lfs2->rcache, diff,
                    dir->pair[0], off+sizeof(tag)+goff, gbuffer, diff);
            if (err) {
                return err;
            }

            memset((uint8_t*)gbuffer + diff, 0, gsize - diff);

            return tag + gdiff;
        }
    }

    return LFS2_ERR_NOENT;
}