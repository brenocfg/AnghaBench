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
struct stream {int dummy; } ;
struct mpv_global {int dummy; } ;
struct mp_cancel {int dummy; } ;
struct demuxer_params {int stream_flags; int demuxer_failed; int /*<<< orphan*/  does_not_own_stream; int /*<<< orphan*/  member_0; } ;
struct demuxer {int /*<<< orphan*/  in; } ;

/* Variables and functions */
 int STREAM_READ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  demux_maybe_replace_stream (struct demuxer*) ; 
 struct demuxer* demux_open (struct stream*,struct demuxer_params*,struct mpv_global*) ; 
 int /*<<< orphan*/  free_stream (struct stream*) ; 
 struct mp_cancel* mp_cancel_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_cancel_set_parent (struct mp_cancel*,struct mp_cancel*) ; 
 struct stream* stream_create (char const*,int,struct mp_cancel*,struct mpv_global*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_cancel*) ; 
 int /*<<< orphan*/  talloc_steal (int /*<<< orphan*/ ,struct mp_cancel*) ; 

struct demuxer *demux_open_url(const char *url,
                               struct demuxer_params *params,
                               struct mp_cancel *cancel,
                               struct mpv_global *global)
{
    struct demuxer_params dummy = {0};
    if (!params)
        params = &dummy;
    assert(!params->does_not_own_stream); // API user error
    struct mp_cancel *priv_cancel = mp_cancel_new(NULL);
    if (cancel)
        mp_cancel_set_parent(priv_cancel, cancel);
    struct stream *s = stream_create(url, STREAM_READ | params->stream_flags,
                                     priv_cancel, global);
    if (!s) {
        talloc_free(priv_cancel);
        return NULL;
    }
    struct demuxer *d = demux_open(s, params, global);
    if (d) {
        talloc_steal(d->in, priv_cancel);
        demux_maybe_replace_stream(d);
    } else {
        params->demuxer_failed = true;
        free_stream(s);
        talloc_free(priv_cancel);
    }
    return d;
}