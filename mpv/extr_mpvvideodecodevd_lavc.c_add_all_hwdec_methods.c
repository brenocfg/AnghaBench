#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct hwdec_info {int use_hw_frames; int use_hw_device; int copying; int /*<<< orphan*/  method_name; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  lavc_device; TYPE_2__ const* codec; } ;
struct TYPE_8__ {scalar_t__ type; int capabilities; char* wrapper_name; } ;
struct TYPE_7__ {int methods; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  device_type; } ;
typedef  TYPE_1__ AVCodecHWConfig ;
typedef  TYPE_2__ AVCodec ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int AV_CODEC_CAP_HARDWARE ; 
 int AV_CODEC_CAP_HYBRID ; 
 int AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX ; 
 int AV_CODEC_HW_CONFIG_METHOD_HW_FRAMES_CTX ; 
 int AV_CODEC_HW_CONFIG_METHOD_INTERNAL ; 
 int /*<<< orphan*/  AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  add_hwdec_item (struct hwdec_info**,int*,struct hwdec_info) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  av_codec_is_decoder (TYPE_2__ const*) ; 
 TYPE_2__* av_codec_iterate (void**) ; 
 char* av_get_pix_fmt_name (int /*<<< orphan*/ ) ; 
 char* av_hwdevice_get_type_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* avcodec_get_hw_config (TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  hwdec_compare ; 
 int /*<<< orphan*/  qsort (struct hwdec_info*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void add_all_hwdec_methods(struct hwdec_info **infos, int *num_infos)
{
    const AVCodec *codec = NULL;
    void *iter = NULL;
    while (1) {
        codec = av_codec_iterate(&iter);
        if (!codec)
            break;
        if (codec->type != AVMEDIA_TYPE_VIDEO || !av_codec_is_decoder(codec))
            continue;

        struct hwdec_info info_template = {
            .pix_fmt = AV_PIX_FMT_NONE,
            .codec = codec,
        };

        const char *wrapper = NULL;
        if (codec->capabilities & (AV_CODEC_CAP_HARDWARE | AV_CODEC_CAP_HYBRID))
            wrapper = codec->wrapper_name;

        // A decoder can provide multiple methods. In particular, hwaccels
        // provide various methods (e.g. native h264 with vaapi & d3d11), but
        // even wrapper decoders could provide multiple methods.
        bool found_any = false;
        for (int n = 0; ; n++) {
            const AVCodecHWConfig *cfg = avcodec_get_hw_config(codec, n);
            if (!cfg)
                break;

            if ((cfg->methods & AV_CODEC_HW_CONFIG_METHOD_HW_FRAMES_CTX) ||
                (cfg->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX))
            {
                struct hwdec_info info = info_template;
                info.lavc_device = cfg->device_type;
                info.pix_fmt = cfg->pix_fmt;

                const char *name = av_hwdevice_get_type_name(cfg->device_type);
                assert(name); // API violation by libavcodec

                // nvdec hwaccels and the cuvid full decoder clash with their
                // naming, so fix it here; we also prefer nvdec for the hwaccel.
                if (strcmp(name, "cuda") == 0 && !wrapper)
                    name = "nvdec";

                snprintf(info.method_name, sizeof(info.method_name), "%s", name);

                // Usually we want to prefer using hw_frames_ctx for true
                // hwaccels only, but we actually don't have any way to detect
                // those, so always use hw_frames_ctx if offered.
                if (cfg->methods & AV_CODEC_HW_CONFIG_METHOD_HW_FRAMES_CTX) {
                    info.use_hw_frames = true;
                } else {
                    info.use_hw_device = true;
                }

                // Direct variant.
                add_hwdec_item(infos, num_infos, info);

                // Copy variant.
                info.copying = true;
                if (cfg->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX) {
                    info.use_hw_frames = false;
                    info.use_hw_device = true;
                }
                add_hwdec_item(infos, num_infos, info);

                found_any = true;
            } else if (cfg->methods & AV_CODEC_HW_CONFIG_METHOD_INTERNAL) {
                struct hwdec_info info = info_template;
                info.pix_fmt = cfg->pix_fmt;

                const char *name = wrapper;
                if (!name)
                    name = av_get_pix_fmt_name(info.pix_fmt);
                assert(name); // API violation by libavcodec

                snprintf(info.method_name, sizeof(info.method_name), "%s", name);

                // Direct variant.
                add_hwdec_item(infos, num_infos, info);

                // Copy variant.
                info.copying = true;
                info.pix_fmt = AV_PIX_FMT_NONE; // trust it can do sw output
                add_hwdec_item(infos, num_infos, info);

                found_any = true;
            }
        }

        if (!found_any && wrapper) {
            // We _know_ there's something supported here, usually outputting
            // sw surfaces. E.g. mediacodec (before hw_device_ctx support).

            struct hwdec_info info = info_template;
            info.copying = true; // probably

            snprintf(info.method_name, sizeof(info.method_name), "%s", wrapper);
            add_hwdec_item(infos, num_infos, info);
        }
    }

    qsort(*infos, *num_infos, sizeof(struct hwdec_info), hwdec_compare);
}