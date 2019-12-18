#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* opts; } ;
typedef  TYPE_2__ vd_ffmpeg_ctx ;
struct mp_filter {TYPE_2__* priv; } ;
struct TYPE_11__ {scalar_t__ len; } ;
typedef  TYPE_3__ bstr ;
struct TYPE_9__ {int /*<<< orphan*/  hwdec_codecs; } ;

/* Variables and functions */
 TYPE_3__ bstr0 (int /*<<< orphan*/ ) ; 
 scalar_t__ bstr_equals0 (TYPE_3__,char const*) ; 
 int /*<<< orphan*/  bstr_split_tok (TYPE_3__,char*,TYPE_3__*,TYPE_3__*) ; 

__attribute__((used)) static bool hwdec_codec_allowed(struct mp_filter *vd, const char *codec)
{
    vd_ffmpeg_ctx *ctx = vd->priv;
    bstr s = bstr0(ctx->opts->hwdec_codecs);
    while (s.len) {
        bstr item;
        bstr_split_tok(s, ",", &item, &s);
        if (bstr_equals0(item, "all") || bstr_equals0(item, codec))
            return true;
    }
    return false;
}