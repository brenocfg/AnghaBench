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
struct mp_decoder {struct mp_filter* f; } ;
struct spdifContext {int use_dts_hd; scalar_t__ codec_id; struct mp_decoder public; int /*<<< orphan*/  pool; int /*<<< orphan*/  log; } ;
struct mp_filter {int /*<<< orphan*/  log; struct spdifContext* priv; } ;
struct mp_codec_params {int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  MP_PIN_IN ; 
 int /*<<< orphan*/  MP_PIN_OUT ; 
 int /*<<< orphan*/  ad_spdif_filter ; 
 int /*<<< orphan*/  mp_aframe_pool_create (struct spdifContext*) ; 
 scalar_t__ mp_codec_to_av_codec_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_filter_add_pin (struct mp_filter*,int /*<<< orphan*/ ,char*) ; 
 struct mp_filter* mp_filter_create (struct mp_filter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_log_new (struct mp_filter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_filter*) ; 

__attribute__((used)) static struct mp_decoder *create(struct mp_filter *parent,
                                 struct mp_codec_params *codec,
                                 const char *decoder)
{
    struct mp_filter *da = mp_filter_create(parent, &ad_spdif_filter);
    if (!da)
        return NULL;

    mp_filter_add_pin(da, MP_PIN_IN, "in");
    mp_filter_add_pin(da, MP_PIN_OUT, "out");

    da->log = mp_log_new(da, parent->log, NULL);

    struct spdifContext *spdif_ctx = da->priv;
    spdif_ctx->log = da->log;
    spdif_ctx->pool = mp_aframe_pool_create(spdif_ctx);
    spdif_ctx->public.f = da;

    if (strcmp(decoder, "spdif_dts_hd") == 0)
        spdif_ctx->use_dts_hd = true;

    spdif_ctx->codec_id = mp_codec_to_av_codec_id(codec->codec);


    if (spdif_ctx->codec_id == AV_CODEC_ID_NONE) {
        talloc_free(da);
        return NULL;
    }
    return &spdif_ctx->public;
}