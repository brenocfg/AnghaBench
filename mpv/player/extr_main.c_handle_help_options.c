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
struct mp_log {int dummy; } ;
struct mp_decoder_list {int dummy; } ;
struct MPOpts {int /*<<< orphan*/  encode_opts; scalar_t__ property_print_help; TYPE_1__* ao_opts; scalar_t__ sub_demuxer_name; scalar_t__ audio_demuxer_name; scalar_t__ demuxer_name; scalar_t__ video_decoders; scalar_t__ audio_spdif; scalar_t__ audio_decoders; } ;
struct MPContext {int /*<<< orphan*/  global; struct mp_log* log; struct MPOpts* opts; } ;
struct TYPE_2__ {scalar_t__ audio_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INFO (struct MPContext*,char*) ; 
 int /*<<< orphan*/  MSGL_INFO ; 
 int /*<<< orphan*/  ao_print_devices (int /*<<< orphan*/ ,struct mp_log*) ; 
 struct mp_decoder_list* audio_decoder_list () ; 
 int /*<<< orphan*/  demuxer_help (struct mp_log*) ; 
 scalar_t__ encode_lavc_showhelp (struct mp_log*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_print_decoders (struct mp_log*,int /*<<< orphan*/ ,char*,struct mp_decoder_list*) ; 
 int /*<<< orphan*/  property_print_help (struct MPContext*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_decoder_list*) ; 
 struct mp_decoder_list* video_decoder_list () ; 

__attribute__((used)) static bool handle_help_options(struct MPContext *mpctx)
{
    struct MPOpts *opts = mpctx->opts;
    struct mp_log *log = mpctx->log;
    if (opts->audio_decoders && strcmp(opts->audio_decoders, "help") == 0) {
        struct mp_decoder_list *list = audio_decoder_list();
        mp_print_decoders(log, MSGL_INFO, "Audio decoders:", list);
        talloc_free(list);
        return true;
    }
    if (opts->audio_spdif && strcmp(opts->audio_spdif, "help") == 0) {
        MP_INFO(mpctx, "Choices: ac3,dts-hd,dts (and possibly more)\n");
        return true;
    }
    if (opts->video_decoders && strcmp(opts->video_decoders, "help") == 0) {
        struct mp_decoder_list *list = video_decoder_list();
        mp_print_decoders(log, MSGL_INFO, "Video decoders:", list);
        talloc_free(list);
        return true;
    }
    if ((opts->demuxer_name && strcmp(opts->demuxer_name, "help") == 0) ||
        (opts->audio_demuxer_name && strcmp(opts->audio_demuxer_name, "help") == 0) ||
        (opts->sub_demuxer_name && strcmp(opts->sub_demuxer_name, "help") == 0)) {
        demuxer_help(log);
        MP_INFO(mpctx, "\n");
        return true;
    }
    if (opts->ao_opts->audio_device &&
        strcmp(opts->ao_opts->audio_device, "help") == 0)
    {
        ao_print_devices(mpctx->global, log);
        return true;
    }
    if (opts->property_print_help) {
        property_print_help(mpctx);
        return true;
    }
    if (encode_lavc_showhelp(log, opts->encode_opts))
        return true;
    return false;
}