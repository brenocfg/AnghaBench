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
struct stream {int dummy; } ;
struct mpv_global {int dummy; } ;
struct mp_cancel {int dummy; } ;
struct TYPE_2__ {scalar_t__ len; } ;
struct demuxer_params {int stream_flags; int demuxer_failed; struct stream* external_stream; TYPE_1__ init_fragment; int /*<<< orphan*/  member_0; } ;
struct demuxer {int /*<<< orphan*/  cancel; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 int STREAM_READ ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct stream* create_webshit_concat_stream (struct mpv_global*,struct mp_cancel*,TYPE_1__,struct stream*) ; 
 struct demuxer* demux_open (struct stream*,struct mp_cancel*,struct demuxer_params*,struct mpv_global*) ; 
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
    struct mp_cancel *priv_cancel = mp_cancel_new(NULL);
    if (cancel)
        mp_cancel_set_parent(priv_cancel, cancel);
    struct stream *s = params->external_stream;
    if (!s) {
        s = stream_create(url, STREAM_READ | params->stream_flags,
                          priv_cancel, global);
        if (s && params->init_fragment.len) {
            s = create_webshit_concat_stream(global, priv_cancel,
                                             params->init_fragment, s);
        }
    }
    if (!s) {
        talloc_free(priv_cancel);
        return NULL;
    }
    struct demuxer *d = demux_open(s, priv_cancel, params, global);
    if (d) {
        talloc_steal(d->in, priv_cancel);
        assert(d->cancel);
    } else {
        params->demuxer_failed = true;
        if (!params->external_stream)
            free_stream(s);
        talloc_free(priv_cancel);
    }
    return d;
}