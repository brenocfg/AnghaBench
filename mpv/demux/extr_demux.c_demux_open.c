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
struct stream {char* demuxer; int /*<<< orphan*/  url; int /*<<< orphan*/  streaming; int /*<<< orphan*/  is_network; int /*<<< orphan*/  seekable; int /*<<< orphan*/  is_directory; } ;
struct parent_stream_info {struct mp_log* filename; struct mp_cancel* cancel; int /*<<< orphan*/  is_streaming; int /*<<< orphan*/  is_network; int /*<<< orphan*/  seekable; } ;
struct mpv_global {int /*<<< orphan*/  log; } ;
struct mp_log {int dummy; } ;
struct mp_cancel {int dummy; } ;
struct demuxer_params {char* force_format; } ;
struct demuxer_desc {int /*<<< orphan*/  name; } ;
struct demuxer {int dummy; } ;
typedef  enum demux_check { ____Placeholder_demux_check } demux_check ;

/* Variables and functions */
 int* d_force ; 
 int /*<<< orphan*/  d_level (int) ; 
 int* d_normal ; 
 int* d_request ; 
 struct demuxer_desc** demuxer_list ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,char*) ; 
 struct mp_log* mp_log_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mp_verbose (struct mp_log*,char*,int /*<<< orphan*/ ) ; 
 struct demuxer* open_given_type (struct mpv_global*,struct mp_log*,struct demuxer_desc const*,struct stream*,struct parent_stream_info*,struct demuxer_params*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_log*) ; 
 int /*<<< orphan*/  talloc_steal (struct demuxer*,struct mp_log*) ; 
 struct mp_log* talloc_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct demuxer *demux_open(struct stream *stream,
                                  struct mp_cancel *cancel,
                                  struct demuxer_params *params,
                                  struct mpv_global *global)
{
    const int *check_levels = d_normal;
    const struct demuxer_desc *check_desc = NULL;
    struct mp_log *log = mp_log_new(NULL, global->log, "!demux");
    struct demuxer *demuxer = NULL;
    char *force_format = params ? params->force_format : NULL;

    if (!force_format)
        force_format = stream->demuxer;

    if (force_format && force_format[0] && !stream->is_directory) {
        check_levels = d_request;
        if (force_format[0] == '+') {
            force_format += 1;
            check_levels = d_force;
        }
        for (int n = 0; demuxer_list[n]; n++) {
            if (strcmp(demuxer_list[n]->name, force_format) == 0)
                check_desc = demuxer_list[n];
        }
        if (!check_desc) {
            mp_err(log, "Demuxer %s does not exist.\n", force_format);
            goto done;
        }
    }

    struct parent_stream_info sinfo = {
        .seekable = stream->seekable,
        .is_network = stream->is_network,
        .is_streaming = stream->streaming,
        .cancel = cancel,
        .filename = talloc_strdup(NULL, stream->url),
    };

    // Test demuxers from first to last, one pass for each check_levels[] entry
    for (int pass = 0; check_levels[pass] != -1; pass++) {
        enum demux_check level = check_levels[pass];
        mp_verbose(log, "Trying demuxers for level=%s.\n", d_level(level));
        for (int n = 0; demuxer_list[n]; n++) {
            const struct demuxer_desc *desc = demuxer_list[n];
            if (!check_desc || desc == check_desc) {
                demuxer = open_given_type(global, log, desc, stream, &sinfo,
                                          params, level);
                if (demuxer) {
                    talloc_steal(demuxer, log);
                    log = NULL;
                    goto done;
                }
            }
        }
    }

done:
    talloc_free(sinfo.filename);
    talloc_free(log);
    return demuxer;
}