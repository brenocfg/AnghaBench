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
struct mux_stream {int /*<<< orphan*/  name; int /*<<< orphan*/  st; } ;
struct encode_priv {int failed; } ;
struct encode_lavc_context {int /*<<< orphan*/  lock; struct encode_priv* priv; } ;
typedef  enum stream_type { ____Placeholder_stream_type } stream_type ;
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct encode_priv*,char*,int /*<<< orphan*/ ) ; 
 struct mux_stream* find_mux_stream (struct encode_lavc_context*,int) ; 
 int mp_to_av_stream_type (int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void encode_lavc_stream_eof(struct encode_lavc_context *ctx,
                            enum stream_type type)
{
    if (!ctx)
        return;

    struct encode_priv *p = ctx->priv;

    pthread_mutex_lock(&ctx->lock);

    enum AVMediaType codec_type = mp_to_av_stream_type(type);
    struct mux_stream *dst = find_mux_stream(ctx, codec_type);

    // If we've reached EOF, even though the stream was selected, and we didn't
    // ever initialize it, we have a problem. We could mux some sort of dummy
    // stream (and could fail if actual data arrives later), or we bail out
    // early.
    if (dst && !dst->st) {
        MP_ERR(p, "No data on stream %s.\n", dst->name);
        p->failed = true;
    }

    pthread_mutex_unlock(&ctx->lock);
}