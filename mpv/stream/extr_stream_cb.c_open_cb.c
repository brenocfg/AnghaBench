#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ (* seek_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cookie; scalar_t__ cancel_fn; int /*<<< orphan*/  close_fn; int /*<<< orphan*/  read_fn; int /*<<< orphan*/  member_0; } ;
struct priv {TYPE_2__ info; int /*<<< orphan*/  cancel; } ;
struct TYPE_10__ {int seekable; int fast_skip; scalar_t__ cancel; int /*<<< orphan*/  close; int /*<<< orphan*/  get_size; int /*<<< orphan*/  fill_buffer; int /*<<< orphan*/  seek; int /*<<< orphan*/  url; int /*<<< orphan*/  global; struct priv* priv; } ;
typedef  TYPE_1__ stream_t ;
typedef  int (* mpv_stream_cb_open_ro_fn ) (void*,int /*<<< orphan*/ ,TYPE_2__*) ;
typedef  TYPE_2__ mpv_stream_cb_info ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 int MPV_ERROR_LOADING_FAILED ; 
 int /*<<< orphan*/  MP_FATAL (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  MP_WARN (TYPE_1__*,char*) ; 
 int STREAM_ERROR ; 
 int STREAM_OK ; 
 int STREAM_UNSUPPORTED ; 
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 
 char* bstrto0 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_buffer ; 
 int /*<<< orphan*/  get_size ; 
 int /*<<< orphan*/  mp_cancel_new (struct priv*) ; 
 int /*<<< orphan*/  mp_cancel_set_cb (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_cancel_set_parent (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mp_split_proto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_streamcb_lookup (int /*<<< orphan*/ ,char*,void**,int (*) (void*,int /*<<< orphan*/ ,TYPE_2__*)) ; 
 struct priv* p ; 
 int /*<<< orphan*/  s_close ; 
 int /*<<< orphan*/  seek ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct priv* talloc_ptrtype (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int open_cb(stream_t *stream)
{
    struct priv *p = talloc_ptrtype(stream, p);
    stream->priv = p;

    bstr bproto = mp_split_proto(bstr0(stream->url), NULL);
    char *proto = bstrto0(stream, bproto);

    void *user_data;
    mpv_stream_cb_open_ro_fn open_fn;

    if (!mp_streamcb_lookup(stream->global, proto, &user_data, &open_fn))
        return STREAM_UNSUPPORTED;

    mpv_stream_cb_info info = {0};

    int r = open_fn(user_data, stream->url, &info);
    if (r < 0) {
        if (r != MPV_ERROR_LOADING_FAILED)
            MP_WARN(stream, "unknown error from user callback\n");
        return STREAM_ERROR;
    }

    if (!info.read_fn || !info.close_fn) {
        MP_FATAL(stream, "required read_fn or close_fn callbacks not set.\n");
        return STREAM_ERROR;
    }

    p->info = info;

    if (p->info.seek_fn && p->info.seek_fn(p->info.cookie, 0) >= 0) {
        stream->seek = seek;
        stream->seekable = true;
    }
    stream->fast_skip = true;
    stream->fill_buffer = fill_buffer;
    stream->get_size = get_size;
    stream->close = s_close;

    if (p->info.cancel_fn && stream->cancel) {
        p->cancel = mp_cancel_new(p);
        mp_cancel_set_parent(p->cancel, stream->cancel);
        mp_cancel_set_cb(p->cancel, p->info.cancel_fn, p->info.cookie);
    }

    return STREAM_OK;
}