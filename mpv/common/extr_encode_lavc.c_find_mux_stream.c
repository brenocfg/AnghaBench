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
struct mux_stream {int codec_type; } ;
struct encode_priv {int num_streams; struct mux_stream** streams; } ;
struct encode_lavc_context {struct encode_priv* priv; } ;
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;

/* Variables and functions */

__attribute__((used)) static struct mux_stream *find_mux_stream(struct encode_lavc_context *ctx,
                                          enum AVMediaType codec_type)
{
    struct encode_priv *p = ctx->priv;

    for (int n = 0; n < p->num_streams; n++) {
        struct mux_stream *s = p->streams[n];
        if (s->codec_type == codec_type)
            return s;
    }

    return NULL;
}