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
struct stat {int dummy; } ;
struct serve_files_priv {int dummy; } ;
struct file_cache_entry {struct cache_funcs const* funcs; } ;
struct cache_funcs {int /*<<< orphan*/  (* init ) (struct file_cache_entry*,struct serve_files_priv*,char const*,struct stat*) ;} ;

/* Variables and functions */
 scalar_t__ LIKELY (int /*<<< orphan*/ ) ; 
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  free (struct file_cache_entry*) ; 
 struct file_cache_entry* malloc (int) ; 
 struct cache_funcs const mmap_funcs ; 
 struct cache_funcs sendfile_funcs ; 
 int /*<<< orphan*/  stub1 (struct file_cache_entry*,struct serve_files_priv*,char const*,struct stat*) ; 

__attribute__((used)) static struct file_cache_entry *
create_cache_entry_from_funcs(struct serve_files_priv *priv,
                              const char *full_path,
                              struct stat *st,
                              const struct cache_funcs *funcs)
{
    struct file_cache_entry *fce;

    fce = malloc(sizeof(*fce));
    if (UNLIKELY(!fce))
        return NULL;

    if (LIKELY(funcs->init(fce, priv, full_path, st))) {
        fce->funcs = funcs;
        return fce;
    }

    free(fce);

    if (funcs != &mmap_funcs)
        return NULL;

    return create_cache_entry_from_funcs(priv, full_path, st, &sendfile_funcs);
}