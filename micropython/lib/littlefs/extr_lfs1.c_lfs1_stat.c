#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct lfs1_info {int /*<<< orphan*/  name; int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;
struct TYPE_15__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_4__ lfs1_t ;
struct TYPE_12__ {int /*<<< orphan*/  size; } ;
struct TYPE_13__ {int /*<<< orphan*/  dir; TYPE_1__ file; } ;
struct TYPE_14__ {int /*<<< orphan*/  nlen; scalar_t__ alen; scalar_t__ elen; TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct TYPE_16__ {TYPE_3__ d; scalar_t__ off; } ;
typedef  TYPE_5__ lfs1_entry_t ;
struct TYPE_17__ {int /*<<< orphan*/ * pair; } ;
typedef  TYPE_6__ lfs1_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  LFS1_TYPE_REG ; 
 int lfs1_bd_read (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lfs1_dir_find (TYPE_4__*,TYPE_6__*,TYPE_5__*,char const**) ; 
 scalar_t__ lfs1_paircmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct lfs1_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int lfs1_stat(lfs1_t *lfs1, const char *path, struct lfs1_info *info) {
    lfs1_dir_t cwd;
    lfs1_entry_t entry;
    int err = lfs1_dir_find(lfs1, &cwd, &entry, &path);
    if (err) {
        return err;
    }

    memset(info, 0, sizeof(*info));
    info->type = entry.d.type;
    if (info->type == LFS1_TYPE_REG) {
        info->size = entry.d.u.file.size;
    }

    if (lfs1_paircmp(entry.d.u.dir, lfs1->root) == 0) {
        strcpy(info->name, "/");
    } else {
        err = lfs1_bd_read(lfs1, cwd.pair[0],
                entry.off + 4+entry.d.elen+entry.d.alen,
                info->name, entry.d.nlen);
        if (err) {
            return err;
        }
    }

    return 0;
}