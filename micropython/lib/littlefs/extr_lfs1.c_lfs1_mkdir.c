#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  deorphaned; } ;
typedef  TYPE_4__ lfs1_t ;
struct TYPE_20__ {int /*<<< orphan*/ * dir; } ;
struct TYPE_21__ {int elen; TYPE_1__ u; int /*<<< orphan*/  nlen; scalar_t__ alen; int /*<<< orphan*/  type; } ;
struct TYPE_24__ {TYPE_2__ d; } ;
typedef  TYPE_5__ lfs1_entry_t ;
struct TYPE_22__ {int /*<<< orphan*/ * tail; } ;
struct TYPE_25__ {int /*<<< orphan*/ * pair; TYPE_3__ d; } ;
typedef  TYPE_6__ lfs1_dir_t ;

/* Variables and functions */
 int LFS1_ERR_EXIST ; 
 int LFS1_ERR_NOENT ; 
 int /*<<< orphan*/  LFS1_TYPE_DIR ; 
 int /*<<< orphan*/  lfs1_alloc_ack (TYPE_4__*) ; 
 int lfs1_deorphan (TYPE_4__*) ; 
 int lfs1_dir_alloc (TYPE_4__*,TYPE_6__*) ; 
 int lfs1_dir_append (TYPE_4__*,TYPE_6__*,TYPE_5__*,char const*) ; 
 int lfs1_dir_commit (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lfs1_dir_find (TYPE_4__*,TYPE_6__*,TYPE_5__*,char const**) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int lfs1_mkdir(lfs1_t *lfs1, const char *path) {
    // deorphan if we haven't yet, needed at most once after poweron
    if (!lfs1->deorphaned) {
        int err = lfs1_deorphan(lfs1);
        if (err) {
            return err;
        }
    }

    // fetch parent directory
    lfs1_dir_t cwd;
    lfs1_entry_t entry;
    int err = lfs1_dir_find(lfs1, &cwd, &entry, &path);
    if (err != LFS1_ERR_NOENT || strchr(path, '/') != NULL) {
        return err ? err : LFS1_ERR_EXIST;
    }

    // build up new directory
    lfs1_alloc_ack(lfs1);

    lfs1_dir_t dir;
    err = lfs1_dir_alloc(lfs1, &dir);
    if (err) {
        return err;
    }
    dir.d.tail[0] = cwd.d.tail[0];
    dir.d.tail[1] = cwd.d.tail[1];

    err = lfs1_dir_commit(lfs1, &dir, NULL, 0);
    if (err) {
        return err;
    }

    entry.d.type = LFS1_TYPE_DIR;
    entry.d.elen = sizeof(entry.d) - 4;
    entry.d.alen = 0;
    entry.d.nlen = strlen(path);
    entry.d.u.dir[0] = dir.pair[0];
    entry.d.u.dir[1] = dir.pair[1];

    cwd.d.tail[0] = dir.pair[0];
    cwd.d.tail[1] = dir.pair[1];

    err = lfs1_dir_append(lfs1, &cwd, &entry, path);
    if (err) {
        return err;
    }

    lfs1_alloc_ack(lfs1);
    return 0;
}