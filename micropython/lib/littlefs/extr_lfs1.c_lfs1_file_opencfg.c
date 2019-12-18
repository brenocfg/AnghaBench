#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_19__ ;

/* Type definitions */
struct lfs1_file_config {void* buffer; } ;
struct TYPE_27__ {TYPE_6__* files; TYPE_4__* cfg; int /*<<< orphan*/  deorphaned; } ;
typedef  TYPE_5__ lfs1_t ;
struct TYPE_22__ {int block; void* buffer; } ;
struct TYPE_28__ {int head; scalar_t__ size; int flags; struct TYPE_28__* next; TYPE_19__ cache; struct lfs1_file_config const* cfg; scalar_t__ pos; int /*<<< orphan*/  poff; int /*<<< orphan*/ * pair; } ;
typedef  TYPE_6__ lfs1_file_t ;
struct TYPE_23__ {int head; scalar_t__ size; } ;
struct TYPE_24__ {TYPE_1__ file; } ;
struct TYPE_25__ {scalar_t__ type; int elen; TYPE_2__ u; int /*<<< orphan*/  nlen; scalar_t__ alen; } ;
struct TYPE_29__ {TYPE_3__ d; int /*<<< orphan*/  off; } ;
typedef  TYPE_7__ lfs1_entry_t ;
struct TYPE_30__ {int /*<<< orphan*/ * pair; } ;
typedef  TYPE_8__ lfs1_dir_t ;
struct TYPE_26__ {int /*<<< orphan*/  prog_size; int /*<<< orphan*/  read_size; void* file_buffer; } ;

/* Variables and functions */
 int LFS1_ERR_EXIST ; 
 int LFS1_ERR_ISDIR ; 
 int LFS1_ERR_NOENT ; 
 int LFS1_ERR_NOMEM ; 
 int LFS1_F_DIRTY ; 
 int LFS1_O_CREAT ; 
 int LFS1_O_EXCL ; 
 int LFS1_O_RDONLY ; 
 int LFS1_O_TRUNC ; 
 scalar_t__ LFS1_TYPE_DIR ; 
 scalar_t__ LFS1_TYPE_REG ; 
 int /*<<< orphan*/  lfs1_cache_drop (TYPE_5__*,TYPE_19__*) ; 
 int /*<<< orphan*/  lfs1_cache_zero (TYPE_5__*,TYPE_19__*) ; 
 int lfs1_deorphan (TYPE_5__*) ; 
 int lfs1_dir_append (TYPE_5__*,TYPE_8__*,TYPE_7__*,char const*) ; 
 int lfs1_dir_find (TYPE_5__*,TYPE_8__*,TYPE_7__*,char const**) ; 
 void* lfs1_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int lfs1_file_opencfg(lfs1_t *lfs1, lfs1_file_t *file,
        const char *path, int flags,
        const struct lfs1_file_config *cfg) {
    // deorphan if we haven't yet, needed at most once after poweron
    if ((flags & 3) != LFS1_O_RDONLY && !lfs1->deorphaned) {
        int err = lfs1_deorphan(lfs1);
        if (err) {
            return err;
        }
    }

    // allocate entry for file if it doesn't exist
    lfs1_dir_t cwd;
    lfs1_entry_t entry;
    int err = lfs1_dir_find(lfs1, &cwd, &entry, &path);
    if (err && (err != LFS1_ERR_NOENT || strchr(path, '/') != NULL)) {
        return err;
    }

    if (err == LFS1_ERR_NOENT) {
        if (!(flags & LFS1_O_CREAT)) {
            return LFS1_ERR_NOENT;
        }

        // create entry to remember name
        entry.d.type = LFS1_TYPE_REG;
        entry.d.elen = sizeof(entry.d) - 4;
        entry.d.alen = 0;
        entry.d.nlen = strlen(path);
        entry.d.u.file.head = 0xffffffff;
        entry.d.u.file.size = 0;
        err = lfs1_dir_append(lfs1, &cwd, &entry, path);
        if (err) {
            return err;
        }
    } else if (entry.d.type == LFS1_TYPE_DIR) {
        return LFS1_ERR_ISDIR;
    } else if (flags & LFS1_O_EXCL) {
        return LFS1_ERR_EXIST;
    }

    // setup file struct
    file->cfg = cfg;
    file->pair[0] = cwd.pair[0];
    file->pair[1] = cwd.pair[1];
    file->poff = entry.off;
    file->head = entry.d.u.file.head;
    file->size = entry.d.u.file.size;
    file->flags = flags;
    file->pos = 0;

    if (flags & LFS1_O_TRUNC) {
        if (file->size != 0) {
            file->flags |= LFS1_F_DIRTY;
        }
        file->head = 0xffffffff;
        file->size = 0;
    }

    // allocate buffer if needed
    file->cache.block = 0xffffffff;
    if (file->cfg && file->cfg->buffer) {
        file->cache.buffer = file->cfg->buffer;
    } else if (lfs1->cfg->file_buffer) {
        if (lfs1->files) {
            // already in use
            return LFS1_ERR_NOMEM;
        }
        file->cache.buffer = lfs1->cfg->file_buffer;
    } else if ((file->flags & 3) == LFS1_O_RDONLY) {
        file->cache.buffer = lfs1_malloc(lfs1->cfg->read_size);
        if (!file->cache.buffer) {
            return LFS1_ERR_NOMEM;
        }
    } else {
        file->cache.buffer = lfs1_malloc(lfs1->cfg->prog_size);
        if (!file->cache.buffer) {
            return LFS1_ERR_NOMEM;
        }
    }

    // zero to avoid information leak
    lfs1_cache_drop(lfs1, &file->cache);
    if ((file->flags & 3) != LFS1_O_RDONLY) {
        lfs1_cache_zero(lfs1, &file->cache);
    }

    // add to list of files
    file->next = lfs1->files;
    lfs1->files = file;

    return 0;
}