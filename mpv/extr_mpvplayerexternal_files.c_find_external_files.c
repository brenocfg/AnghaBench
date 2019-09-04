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
struct subfn {int /*<<< orphan*/  member_0; } ;
struct mpv_global {int dummy; } ;
struct MPOpts {scalar_t__ sub_auto; scalar_t__ audiofile_auto; int /*<<< orphan*/  audiofile_paths; int /*<<< orphan*/  sub_paths; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (int /*<<< orphan*/ *,struct subfn*,int,struct subfn) ; 
 int /*<<< orphan*/  STREAM_AUDIO ; 
 int /*<<< orphan*/  STREAM_SUB ; 
 int /*<<< orphan*/  append_dir_subtitles (struct mpv_global*,struct MPOpts*,struct subfn**,int*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  compare_sub_filename ; 
 int /*<<< orphan*/  compare_sub_priority ; 
 int /*<<< orphan*/  filter_subidx (struct subfn**,int*) ; 
 int /*<<< orphan*/  load_paths (struct mpv_global*,struct MPOpts*,struct subfn**,int*,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_dirname (char const*) ; 
 int /*<<< orphan*/  qsort (struct subfn*,int,int,int /*<<< orphan*/ ) ; 
 struct subfn* slist ; 
 struct subfn* talloc_array_ptrtype (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

struct subfn *find_external_files(struct mpv_global *global, const char *fname,
                                  struct MPOpts *opts)
{
    struct subfn *slist = talloc_array_ptrtype(NULL, slist, 1);
    int n = 0;

    // Load subtitles from current media directory
    append_dir_subtitles(global, opts, &slist, &n, mp_dirname(fname), fname, 0, -1);

    // Load subtitles in dirs specified by sub-paths option
    if (opts->sub_auto >= 0) {
        load_paths(global, opts, &slist, &n, fname, opts->sub_paths, "sub",
                   STREAM_SUB);
    }

    if (opts->audiofile_auto >= 0) {
        load_paths(global, opts, &slist, &n, fname, opts->audiofile_paths,
                   "audio", STREAM_AUDIO);
    }

    // Sort by name for filter_subidx()
    qsort(slist, n, sizeof(*slist), compare_sub_filename);

    filter_subidx(&slist, &n);

    // Sort subs by priority and append them
    qsort(slist, n, sizeof(*slist), compare_sub_priority);

    struct subfn z = {0};
    MP_TARRAY_APPEND(NULL, slist, n, z);

    return slist;
}