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
struct stat {int st_size; int /*<<< orphan*/  st_mode; } ;
struct serve_files_priv {int root_path_len; int /*<<< orphan*/  auto_index; int /*<<< orphan*/  root_fd; scalar_t__ index_html; } ;
struct cache_funcs {int dummy; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ LIKELY (int /*<<< orphan*/ ) ; 
 int PATH_MAX ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ UNLIKELY (int) ; 
 struct cache_funcs const dirlist_funcs ; 
 scalar_t__ errno ; 
 scalar_t__ fstatat (int /*<<< orphan*/ ,char*,struct stat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_world_readable (int /*<<< orphan*/ ) ; 
 struct cache_funcs const mmap_funcs ; 
 char* rawmemchr (char const*,char) ; 
 struct cache_funcs const redir_funcs ; 
 struct cache_funcs const sendfile_funcs ; 
 int snprintf (char*,int,char*,char const*,scalar_t__) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static const struct cache_funcs *get_funcs(struct serve_files_priv *priv,
                                           const char *key,
                                           char *full_path,
                                           struct stat *st)
{
    char index_html_path_buf[PATH_MAX];
    char *index_html_path = index_html_path_buf;

    if (S_ISDIR(st->st_mode)) {
        /* It is a directory. It might be the root directory (empty key), or
         * something else.  In either case, tack priv->index_html to the
         * path.  */
        if (*key == '\0') {
            index_html_path = (char *)priv->index_html;
        } else {
            /* Redirect /path to /path/. This is to help cases where there's
             * something like <img src="../foo.png">, so that actually
             * /path/../foo.png is served instead of /path../foo.png.  */
            const char *key_end = rawmemchr(key, '\0');
            if (*(key_end - 1) != '/')
                return &redir_funcs;

            int ret = snprintf(index_html_path, PATH_MAX, "%s%s", key,
                               priv->index_html);
            if (UNLIKELY(ret < 0 || ret >= PATH_MAX))
                return NULL;
        }

        /* See if it exists. */
        if (fstatat(priv->root_fd, index_html_path, st, 0) < 0) {
            if (UNLIKELY(errno != ENOENT))
                return NULL;

            if (LIKELY(priv->auto_index)) {
                /* If it doesn't, we want to generate a directory list. */
                return &dirlist_funcs;
            }

            /* Auto index is disabled. */
            return NULL;
        }

        /* Only serve world-readable indexes. */
        if (UNLIKELY(!is_world_readable(st->st_mode)))
            return NULL;

        /* If it does, we want its full path. */

        /* FIXME: Use strlcpy() here instead of calling strlen()? */
        if (UNLIKELY(priv->root_path_len + 1 /* slash */ +
                         strlen(index_html_path) + 1 >=
                     PATH_MAX))
            return NULL;

        full_path[priv->root_path_len] = '/';
        strncpy(full_path + priv->root_path_len + 1, index_html_path,
                PATH_MAX - priv->root_path_len - 1);
    }

    /* Only serve regular files. */
    if (UNLIKELY(!S_ISREG(st->st_mode)))
        return NULL;

    /* It's not a directory: choose the fastest way to serve the file
     * judging by its size. */
    if (st->st_size < 16384)
        return &mmap_funcs;

    return &sendfile_funcs;
}