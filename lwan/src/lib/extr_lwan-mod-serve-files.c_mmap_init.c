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
struct stat {scalar_t__ st_size; } ;
struct serve_files_priv {int root_path_len; int /*<<< orphan*/  root_fd; } ;
struct TYPE_4__ {scalar_t__ value; size_t len; } ;
struct mmap_cache_data {int /*<<< orphan*/  deflated; int /*<<< orphan*/  zstd; TYPE_1__ uncompressed; int /*<<< orphan*/  brotli; } ;
struct file_cache_entry {int /*<<< orphan*/  mime_type; struct mmap_cache_data mmap_cache_data; } ;

/* Variables and functions */
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  PROT_READ ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  brotli_value (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  deflate_value (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwan_determine_mime_type_for_file_name (char const*) ; 
 int /*<<< orphan*/  lwan_madvise_queue (scalar_t__,size_t) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_mode ; 
 int openat (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zstd_value (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool mmap_init(struct file_cache_entry *ce,
                      struct serve_files_priv *priv,
                      const char *full_path,
                      struct stat *st)
{
    struct mmap_cache_data *md = &ce->mmap_cache_data;
    const char *path = full_path + priv->root_path_len;
    int file_fd;
    bool success;

    path += *path == '/';

    file_fd = openat(priv->root_fd, path, open_mode);
    if (UNLIKELY(file_fd < 0))
        return false;

    md->uncompressed.value =
        mmap(NULL, (size_t)st->st_size, PROT_READ, MAP_SHARED, file_fd, 0);
    if (UNLIKELY(md->uncompressed.value == MAP_FAILED)) {
        success = false;
        goto close_file;
    }

    lwan_madvise_queue(md->uncompressed.value, (size_t)st->st_size);

    md->uncompressed.len = (size_t)st->st_size;
    deflate_value(&md->uncompressed, &md->deflated);
#if defined(HAVE_BROTLI)
    brotli_value(&md->uncompressed, &md->brotli, &md->deflated);
#endif
#if defined(HAVE_ZSTD)
    zstd_value(&md->uncompressed, &md->zstd, &md->deflated);
#endif

    ce->mime_type =
        lwan_determine_mime_type_for_file_name(full_path + priv->root_path_len);

    success = true;

close_file:
    close(file_fd);

    return success;
}