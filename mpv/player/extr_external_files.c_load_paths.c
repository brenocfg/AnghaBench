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
struct subfn {int dummy; } ;
struct mpv_global {int dummy; } ;
struct MPOpts {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  append_dir_subtitles (struct mpv_global*,struct MPOpts*,struct subfn**,int*,int /*<<< orphan*/ ,char const*,int,int) ; 
 int /*<<< orphan*/  bstr0 (char*) ; 
 int /*<<< orphan*/  mp_dirname (char const*) ; 
 char* mp_find_config_file (int /*<<< orphan*/ *,struct mpv_global*,char*) ; 
 char* mp_get_user_path (int /*<<< orphan*/ *,struct mpv_global*,char*) ; 
 char* mp_path_join_bstr (struct subfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

__attribute__((used)) static void load_paths(struct mpv_global *global, struct MPOpts *opts,
                       struct subfn **slist, int *nsubs, const char *fname,
                       char **paths, char *cfg_path, int type)
{
    for (int i = 0; paths && paths[i]; i++) {
        char *expanded_path = mp_get_user_path(NULL, global, paths[i]);
        char *path = mp_path_join_bstr(
            *slist, mp_dirname(fname),
            bstr0(expanded_path ? expanded_path : paths[i]));
        append_dir_subtitles(global, opts, slist, nsubs, bstr0(path),
                             fname, 0, type);
        talloc_free(expanded_path);
    }

    // Load subtitles in ~/.mpv/sub (or similar) limiting sub fuzziness
    char *mp_subdir = mp_find_config_file(NULL, global, cfg_path);
    if (mp_subdir) {
        append_dir_subtitles(global, opts, slist, nsubs, bstr0(mp_subdir),
                             fname, 1, type);
    }
    talloc_free(mp_subdir);
}