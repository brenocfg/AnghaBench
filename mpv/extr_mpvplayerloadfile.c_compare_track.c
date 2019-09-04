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
struct track {scalar_t__ is_external; scalar_t__ auto_loaded; scalar_t__ forced_track; scalar_t__ default_track; scalar_t__ attached_picture; scalar_t__ user_tid; TYPE_1__* stream; int /*<<< orphan*/  lang; int /*<<< orphan*/  no_default; } ;
struct MPOpts {scalar_t__ hls_bitrate; int /*<<< orphan*/  autoload_files; } ;
struct TYPE_2__ {scalar_t__ hls_bitrate; } ;

/* Variables and functions */
 int match_lang (char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool compare_track(struct track *t1, struct track *t2, char **langs,
                          struct MPOpts *opts)
{
    if (!opts->autoload_files && t1->is_external != t2->is_external)
        return !t1->is_external;
    bool ext1 = t1->is_external && !t1->no_default;
    bool ext2 = t2->is_external && !t2->no_default;
    if (ext1 != ext2)
        return ext1;
    if (t1->auto_loaded != t2->auto_loaded)
        return !t1->auto_loaded;
    int l1 = match_lang(langs, t1->lang), l2 = match_lang(langs, t2->lang);
    if (l1 != l2)
        return l1 > l2;
    if (t1->forced_track != t2->forced_track)
        return t1->forced_track;
    if (t1->default_track != t2->default_track)
        return t1->default_track;
    if (t1->attached_picture != t2->attached_picture)
        return !t1->attached_picture;
    if (t1->stream && t2->stream && opts->hls_bitrate >= 0 &&
        t1->stream->hls_bitrate != t2->stream->hls_bitrate)
    {
        bool t1_ok = t1->stream->hls_bitrate <= opts->hls_bitrate;
        bool t2_ok = t2->stream->hls_bitrate <= opts->hls_bitrate;
        if (t1_ok != t2_ok)
            return t1_ok;
        if (t1_ok && t2_ok)
            return t1->stream->hls_bitrate > t2->stream->hls_bitrate;
        return t1->stream->hls_bitrate < t2->stream->hls_bitrate;
    }
    return t1->user_tid <= t2->user_tid;
}