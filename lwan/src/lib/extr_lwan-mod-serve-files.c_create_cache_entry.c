#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_mode; } ;
struct serve_files_priv {int /*<<< orphan*/  root_path_len; int /*<<< orphan*/  root_path; int /*<<< orphan*/  root_fd; } ;
struct TYPE_2__ {int /*<<< orphan*/  integer; int /*<<< orphan*/  string; } ;
struct file_cache_entry {TYPE_1__ last_modified; } ;
struct cache_funcs {int dummy; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ UNLIKELY (int) ; 
 struct file_cache_entry* create_cache_entry_from_funcs (struct serve_files_priv*,char*,struct stat*,struct cache_funcs const*) ; 
 int /*<<< orphan*/  destroy_cache_entry (struct cache_entry*,int /*<<< orphan*/ *) ; 
 struct cache_funcs* get_funcs (struct serve_files_priv*,char const*,char*,struct stat*) ; 
 int /*<<< orphan*/  is_world_readable (int /*<<< orphan*/ ) ; 
 scalar_t__ lwan_format_rfc_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  realpathat2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char*,struct stat*) ; 
 int strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cache_entry *create_cache_entry(const char *key, void *context)
{
    struct serve_files_priv *priv = context;
    struct file_cache_entry *fce;
    struct stat st;
    const struct cache_funcs *funcs;
    char full_path[PATH_MAX];

    if (UNLIKELY(
            !realpathat2(priv->root_fd, priv->root_path, key, full_path, &st)))
        return NULL;

    if (UNLIKELY(!is_world_readable(st.st_mode)))
        return NULL;

    if (UNLIKELY(strncmp(full_path, priv->root_path, priv->root_path_len)))
        return NULL;

    funcs = get_funcs(priv, key, full_path, &st);
    if (UNLIKELY(!funcs))
        return NULL;

    fce = create_cache_entry_from_funcs(priv, full_path, &st, funcs);
    if (UNLIKELY(!fce))
        return NULL;

    if (UNLIKELY(lwan_format_rfc_time(st.st_mtime, fce->last_modified.string) <
                 0)) {
        destroy_cache_entry((struct cache_entry *)fce, NULL);
        return NULL;
    }
    fce->last_modified.integer = st.st_mtime;

    return (struct cache_entry *)fce;
}