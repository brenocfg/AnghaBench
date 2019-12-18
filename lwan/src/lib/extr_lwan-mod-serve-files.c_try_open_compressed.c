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
struct stat {scalar_t__ st_mtime; scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
struct serve_files_priv {int /*<<< orphan*/  root_fd; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ LIKELY (int /*<<< orphan*/ ) ; 
 int PATH_MAX ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/  is_compression_worthy (size_t,size_t) ; 
 int /*<<< orphan*/  is_world_readable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_mode ; 
 int openat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  try_readahead (struct serve_files_priv const*,int,size_t) ; 

__attribute__((used)) static int try_open_compressed(const char *relpath,
                               const struct serve_files_priv *priv,
                               const struct stat *uncompressed,
                               size_t *compressed_sz)
{
    char gzpath[PATH_MAX];
    struct stat st;
    int ret, fd;

    /* Try to serve a compressed file using sendfile() if $FILENAME.gz exists */
    ret = snprintf(gzpath, PATH_MAX, "%s.gz", relpath + 1);
    if (UNLIKELY(ret < 0 || ret >= PATH_MAX))
        goto out;

    fd = openat(priv->root_fd, gzpath, open_mode);
    if (UNLIKELY(fd < 0))
        goto out;

    ret = fstat(fd, &st);
    if (UNLIKELY(ret < 0))
        goto close_and_out;

    if (UNLIKELY(st.st_mtime < uncompressed->st_mtime))
        goto close_and_out;

    if (UNLIKELY(!is_world_readable(st.st_mode)))
        goto close_and_out;

    if (LIKELY(is_compression_worthy((size_t)st.st_size,
                                     (size_t)uncompressed->st_size))) {
        *compressed_sz = (size_t)st.st_size;

        try_readahead(priv, fd, *compressed_sz);

        return fd;
    }

close_and_out:
    close(fd);
out:
    *compressed_sz = 0;
    return -ENOENT;
}