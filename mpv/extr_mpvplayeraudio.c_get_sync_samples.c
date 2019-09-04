#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_chmap {int dummy; } ;
struct MPOpts {double audio_delay; int /*<<< orphan*/  initial_audio_sync; } ;
struct MPContext {scalar_t__ audio_status; int audio_speed; scalar_t__ video_status; double video_pts; double hrseek_pts; double playback_pts; scalar_t__ hrseek_active; TYPE_2__* vo_chain; TYPE_1__* ao_chain; int /*<<< orphan*/  ao; struct MPOpts* opts; } ;
struct TYPE_4__ {int /*<<< orphan*/  is_coverart; } ;
struct TYPE_3__ {int /*<<< orphan*/  ao_buffer; } ;

/* Variables and functions */
 double MPCLAMP (double,int,int) ; 
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_WARN (struct MPContext*,char*) ; 
 scalar_t__ STATUS_EOF ; 
 void* STATUS_FILLING ; 
 scalar_t__ STATUS_READY ; 
 scalar_t__ STATUS_SYNCING ; 
 int af_format_sample_alignment (int) ; 
 int /*<<< orphan*/  ao_get_format (int /*<<< orphan*/ ,int*,int*,struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_audio_buffer_samples (int /*<<< orphan*/ ) ; 
 double written_audio_pts (struct MPContext*) ; 

__attribute__((used)) static bool get_sync_samples(struct MPContext *mpctx, int *skip)
{
    struct MPOpts *opts = mpctx->opts;
    *skip = 0;

    if (mpctx->audio_status != STATUS_SYNCING)
        return true;

    int ao_rate;
    int ao_format;
    struct mp_chmap ao_channels;
    ao_get_format(mpctx->ao, &ao_rate, &ao_format, &ao_channels);

    double play_samplerate = ao_rate / mpctx->audio_speed;

    if (!opts->initial_audio_sync) {
        mpctx->audio_status = STATUS_FILLING;
        return true;
    }

    double written_pts = written_audio_pts(mpctx);
    if (written_pts == MP_NOPTS_VALUE &&
        !mp_audio_buffer_samples(mpctx->ao_chain->ao_buffer))
        return false; // no audio read yet

    bool sync_to_video = mpctx->vo_chain && !mpctx->vo_chain->is_coverart &&
                         mpctx->video_status != STATUS_EOF;

    double sync_pts = MP_NOPTS_VALUE;
    if (sync_to_video) {
        if (mpctx->video_status < STATUS_READY)
            return false; // wait until we know a video PTS
        if (mpctx->video_pts != MP_NOPTS_VALUE)
            sync_pts = mpctx->video_pts - opts->audio_delay;
    } else if (mpctx->hrseek_active) {
        sync_pts = mpctx->hrseek_pts;
    } else {
        // If audio-only is enabled mid-stream during playback, sync accordingly.
        sync_pts = mpctx->playback_pts;
    }
    if (sync_pts == MP_NOPTS_VALUE) {
        mpctx->audio_status = STATUS_FILLING;
        return true; // syncing disabled
    }

    double ptsdiff = written_pts - sync_pts;

    // Missing timestamp, or PTS reset, or just broken.
    if (written_pts == MP_NOPTS_VALUE) {
        MP_WARN(mpctx, "Failed audio resync.\n");
        mpctx->audio_status = STATUS_FILLING;
        return true;
    }
    ptsdiff = MPCLAMP(ptsdiff, -3600, 3600);

    int align = af_format_sample_alignment(ao_format);
    *skip = (int)(-ptsdiff * play_samplerate) / align * align;
    return true;
}