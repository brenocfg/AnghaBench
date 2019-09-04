#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hwdec_info {char* method_name; char* name; TYPE_3__* codec; int /*<<< orphan*/  copying; scalar_t__ lavc_device; } ;
struct TYPE_8__ {int hwdec_requested; int use_hwdec; char const* decoder; struct hwdec_info hwdec; scalar_t__ hwdec_devs; int /*<<< orphan*/  hwdec_dev; TYPE_2__* opts; int /*<<< orphan*/  opts_cache; TYPE_1__* codec; } ;
typedef  TYPE_4__ vd_ffmpeg_ctx ;
struct mp_filter {TYPE_4__* priv; } ;
struct hwcontext_fns {scalar_t__ (* is_emulated ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  bstr ;
struct TYPE_7__ {char const* name; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  hwdec_api; } ;
struct TYPE_5__ {char* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct mp_filter*,char*,...) ; 
 int /*<<< orphan*/  MP_WARN (struct mp_filter*,char*) ; 
 int /*<<< orphan*/  add_all_hwdec_methods (struct hwdec_info**,int*) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 
 int bstr_equals0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hwdec_codec_allowed (struct mp_filter*,char const*) ; 
 int /*<<< orphan*/  hwdec_create_dev (struct mp_filter*,struct hwdec_info*,int) ; 
 int /*<<< orphan*/  hwdec_devices_request_all (scalar_t__) ; 
 struct hwcontext_fns* hwdec_get_hwcontext_fns (scalar_t__) ; 
 int /*<<< orphan*/  m_config_cache_update (int /*<<< orphan*/ ) ; 
 char* mp_codec_from_av_codec_id (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct hwdec_info*) ; 

__attribute__((used)) static void select_and_set_hwdec(struct mp_filter *vd)
{
    vd_ffmpeg_ctx *ctx = vd->priv;
    const char *codec = ctx->codec->codec;

    m_config_cache_update(ctx->opts_cache);

    bstr opt = bstr0(ctx->opts->hwdec_api);

    bool hwdec_requested = !bstr_equals0(opt, "no");
    bool hwdec_auto_all = bstr_equals0(opt, "auto") ||
                          bstr_equals0(opt, "yes") ||
                          bstr_equals0(opt, "");
    bool hwdec_auto_copy = bstr_equals0(opt, "auto-copy");
    bool hwdec_auto = hwdec_auto_all || hwdec_auto_copy;

    if (!hwdec_requested) {
        MP_VERBOSE(vd, "No hardware decoding requested.\n");
    } else if (!hwdec_codec_allowed(vd, codec)) {
        MP_VERBOSE(vd, "Not trying to use hardware decoding: codec %s is not "
                   "on whitelist.\n", codec);
    } else {
        struct hwdec_info *hwdecs = NULL;
        int num_hwdecs = 0;
        add_all_hwdec_methods(&hwdecs, &num_hwdecs);

        ctx->hwdec_requested = true;

        for (int n = 0; n < num_hwdecs; n++) {
            struct hwdec_info *hwdec = &hwdecs[n];

            const char *hw_codec = mp_codec_from_av_codec_id(hwdec->codec->id);
            if (!hw_codec || strcmp(hw_codec, codec) != 0)
                continue;

            if (!hwdec_auto && !(bstr_equals0(opt, hwdec->method_name) ||
                                 bstr_equals0(opt, hwdec->name)))
                continue;

            MP_VERBOSE(vd, "Looking at hwdec %s...\n", hwdec->name);

            if (hwdec_auto_copy && !hwdec->copying) {
                MP_VERBOSE(vd, "Not using this for auto-copy.\n");
                continue;
            }

            if (hwdec->lavc_device) {
                ctx->hwdec_dev = hwdec_create_dev(vd, hwdec, hwdec_auto);
                if (!ctx->hwdec_dev) {
                    MP_VERBOSE(vd, "Could not create device.\n");
                    continue;
                }

                const struct hwcontext_fns *fns =
                            hwdec_get_hwcontext_fns(hwdec->lavc_device);
                if (fns && fns->is_emulated && fns->is_emulated(ctx->hwdec_dev)) {
                    if (hwdec_auto) {
                        MP_VERBOSE(vd, "Not using emulated API.\n");
                        av_buffer_unref(&ctx->hwdec_dev);
                        continue;
                    }
                    MP_WARN(vd, "Using emulated hardware decoding API.\n");
                }
            } else if (!hwdec->copying) {
                // Most likely METHOD_INTERNAL, which often use delay-loaded
                // VO support as well.
                if (ctx->hwdec_devs)
                    hwdec_devices_request_all(ctx->hwdec_devs);
            }

            ctx->use_hwdec = true;
            ctx->hwdec = *hwdec;
            break;
        }

        talloc_free(hwdecs);

        if (!ctx->use_hwdec)
            MP_VERBOSE(vd, "No hardware decoding available for this codec.\n");
    }

    if (ctx->use_hwdec) {
        MP_VERBOSE(vd, "Trying hardware decoding via %s.\n", ctx->hwdec.name);
        if (strcmp(ctx->decoder, ctx->hwdec.codec->name) != 0)
            MP_VERBOSE(vd, "Using underlying hw-decoder '%s'\n",
                       ctx->hwdec.codec->name);
    } else {
        MP_VERBOSE(vd, "Using software decoding.\n");
    }
}