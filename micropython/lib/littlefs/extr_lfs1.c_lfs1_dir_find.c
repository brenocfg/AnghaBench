#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  moving; int /*<<< orphan*/ * root; } ;
typedef  TYPE_2__ lfs1_t ;
struct TYPE_20__ {int /*<<< orphan*/ * dir; } ;
struct TYPE_16__ {int type; int elen; size_t nlen; TYPE_6__ u; scalar_t__ alen; } ;
struct TYPE_18__ {TYPE_1__ d; scalar_t__ off; } ;
typedef  TYPE_3__ lfs1_entry_t ;
struct TYPE_19__ {int /*<<< orphan*/ * pair; } ;
typedef  TYPE_4__ lfs1_dir_t ;

/* Variables and functions */
 int LFS1_ERR_NOENT ; 
 int LFS1_ERR_NOTDIR ; 
 int LFS1_TYPE_DIR ; 
 int LFS1_TYPE_REG ; 
 int lfs1_bd_cmp (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,char const*,size_t) ; 
 int lfs1_dir_fetch (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int lfs1_dir_next (TYPE_2__*,TYPE_4__*,TYPE_3__*) ; 
 int lfs1_moved (TYPE_2__*,TYPE_6__*) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 size_t strcspn (char const*,char*) ; 
 int /*<<< orphan*/  strspn (char const*,char*) ; 

__attribute__((used)) static int lfs1_dir_find(lfs1_t *lfs1, lfs1_dir_t *dir,
        lfs1_entry_t *entry, const char **path) {
    const char *pathname = *path;
    size_t pathlen;
    entry->d.type = LFS1_TYPE_DIR;
    entry->d.elen = sizeof(entry->d) - 4;
    entry->d.alen = 0;
    entry->d.nlen = 0;
    entry->d.u.dir[0] = lfs1->root[0];
    entry->d.u.dir[1] = lfs1->root[1];

    while (true) {
nextname:
        // skip slashes
        pathname += strspn(pathname, "/");
        pathlen = strcspn(pathname, "/");

        // skip '.' and root '..'
        if ((pathlen == 1 && memcmp(pathname, ".", 1) == 0) ||
            (pathlen == 2 && memcmp(pathname, "..", 2) == 0)) {
            pathname += pathlen;
            goto nextname;
        }

        // skip if matched by '..' in name
        const char *suffix = pathname + pathlen;
        size_t sufflen;
        int depth = 1;
        while (true) {
            suffix += strspn(suffix, "/");
            sufflen = strcspn(suffix, "/");
            if (sufflen == 0) {
                break;
            }

            if (sufflen == 2 && memcmp(suffix, "..", 2) == 0) {
                depth -= 1;
                if (depth == 0) {
                    pathname = suffix + sufflen;
                    goto nextname;
                }
            } else {
                depth += 1;
            }

            suffix += sufflen;
        }

        // found path
        if (pathname[0] == '\0') {
            return 0;
        }

        // update what we've found
        *path = pathname;

        // continue on if we hit a directory
        if (entry->d.type != LFS1_TYPE_DIR) {
            return LFS1_ERR_NOTDIR;
        }

        int err = lfs1_dir_fetch(lfs1, dir, entry->d.u.dir);
        if (err) {
            return err;
        }

        // find entry matching name
        while (true) {
            err = lfs1_dir_next(lfs1, dir, entry);
            if (err) {
                return err;
            }

            if (((0x7f & entry->d.type) != LFS1_TYPE_REG &&
                 (0x7f & entry->d.type) != LFS1_TYPE_DIR) ||
                entry->d.nlen != pathlen) {
                continue;
            }

            int res = lfs1_bd_cmp(lfs1, dir->pair[0],
                    entry->off + 4+entry->d.elen+entry->d.alen,
                    pathname, pathlen);
            if (res < 0) {
                return res;
            }

            // found match
            if (res) {
                break;
            }
        }

        // check that entry has not been moved
        if (!lfs1->moving && entry->d.type & 0x80) {
            int moved = lfs1_moved(lfs1, &entry->d.u);
            if (moved < 0 || moved) {
                return (moved < 0) ? moved : LFS1_ERR_NOENT;
            }

            entry->d.type &= ~0x80;
        }

        // to next name
        pathname += pathlen;
    }
}