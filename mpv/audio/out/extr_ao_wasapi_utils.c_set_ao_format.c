#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ao_convert_fmt {scalar_t__ pad_lsb; scalar_t__ dst_bits; int /*<<< orphan*/  channels; scalar_t__ src_fmt; } ;
struct wasapi_state {scalar_t__ share_mode; int /*<<< orphan*/  format; struct ao_convert_fmt convert_format; } ;
struct wasapi_sample_fmt {scalar_t__ mp_format; scalar_t__ used_msb; scalar_t__ bits; } ;
struct mp_chmap {int /*<<< orphan*/  num; } ;
struct ao {int /*<<< orphan*/  samplerate; scalar_t__ format; struct mp_chmap channels; struct wasapi_state* priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  nSamplesPerSec; } ;
typedef  TYPE_1__ WAVEFORMATEX ;
typedef  scalar_t__ AUDCLNT_SHAREMODE ;

/* Variables and functions */
 scalar_t__ AUDCLNT_SHAREMODE_EXCLUSIVE ; 
 int /*<<< orphan*/  MP_ERR (struct ao*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ af_fmt_is_pcm (scalar_t__) ; 
 int /*<<< orphan*/  af_fmt_to_str (scalar_t__) ; 
 int /*<<< orphan*/  ao_can_convert_inplace (struct ao_convert_fmt*) ; 
 int /*<<< orphan*/  chmap_from_waveformat (struct mp_chmap*,TYPE_1__*) ; 
 struct wasapi_sample_fmt format_from_waveformat (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_chmap_to_str (struct mp_chmap*) ; 
 int /*<<< orphan*/  waveformat_copy (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  waveformat_to_str (TYPE_1__*) ; 

__attribute__((used)) static bool set_ao_format(struct ao *ao, WAVEFORMATEX *wf,
                          AUDCLNT_SHAREMODE share_mode)
{
    struct wasapi_state *state = ao->priv;
    struct wasapi_sample_fmt format = format_from_waveformat(wf);
    if (!format.mp_format) {
        MP_ERR(ao, "Unable to construct sample format from WAVEFORMAT %s\n",
               waveformat_to_str(wf));
        return false;
    }

    // Do not touch the ao for passthrough, just assume that we set WAVEFORMATEX
    // correctly.
    if (af_fmt_is_pcm(format.mp_format)) {
        struct mp_chmap channels;
        if (!chmap_from_waveformat(&channels, wf)) {
            MP_ERR(ao, "Unable to construct channel map from WAVEFORMAT %s\n",
                   waveformat_to_str(wf));
            return false;
        }

        struct ao_convert_fmt conv = {
            .src_fmt    = format.mp_format,
            .channels   = channels.num,
            .dst_bits   = format.bits,
            .pad_lsb    = format.bits - format.used_msb,
        };
        if (!ao_can_convert_inplace(&conv)) {
            MP_ERR(ao, "Unable to convert to %s\n", waveformat_to_str(wf));
            return false;
        }

        state->convert_format = conv;
        ao->samplerate = wf->nSamplesPerSec;
        ao->format     = format.mp_format;
        ao->channels   = channels;
    }
    waveformat_copy(&state->format, wf);
    state->share_mode = share_mode;

    MP_VERBOSE(ao, "Accepted as %s %s @ %dhz -> %s (%s)\n",
               mp_chmap_to_str(&ao->channels),
               af_fmt_to_str(ao->format), ao->samplerate,
               waveformat_to_str(wf),
               state->share_mode == AUDCLNT_SHAREMODE_EXCLUSIVE
               ? "exclusive" : "shared");
    return true;
}