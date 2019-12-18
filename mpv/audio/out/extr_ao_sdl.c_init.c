#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct priv {int buflen; int paused; } ;
struct mp_chmap_sel {int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {scalar_t__ num; } ;
struct ao {scalar_t__ format; int samplerate; int device_buffer; TYPE_2__ channels; int /*<<< orphan*/  probing; struct priv* priv; } ;
struct TYPE_6__ {scalar_t__ format; int freq; int samples; scalar_t__ channels; struct ao* userdata; int /*<<< orphan*/  callback; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SDL_AudioSpec ;

/* Variables and functions */
 scalar_t__ AUDIO_S16SYS ; 
 int MPMIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_ERR (struct ao*,char*,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 int /*<<< orphan*/  SDL_INIT_AUDIO ; 
 scalar_t__ SDL_InitSubSystem (int /*<<< orphan*/ ) ; 
 scalar_t__ SDL_OpenAudio (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ SDL_WasInit (int /*<<< orphan*/ ) ; 
 scalar_t__ af_fmt_from_planar (scalar_t__) ; 
 int /*<<< orphan*/  ao_chmap_sel_adjust (struct ao*,struct mp_chmap_sel*,TYPE_2__*) ; 
 int /*<<< orphan*/  ao_chmap_sel_get_def (struct ao*,struct mp_chmap_sel*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  audio_callback ; 
 int /*<<< orphan*/  ceil_power_of_two (int) ; 
 scalar_t__** fmtmap ; 
 int /*<<< orphan*/  mp_chmap_sel_add_waveext_def (struct mp_chmap_sel*) ; 
 int /*<<< orphan*/  uninit (struct ao*) ; 

__attribute__((used)) static int init(struct ao *ao)
{
    if (SDL_WasInit(SDL_INIT_AUDIO)) {
        MP_ERR(ao, "already initialized\n");
        return -1;
    }

    struct priv *priv = ao->priv;

    if (SDL_InitSubSystem(SDL_INIT_AUDIO)) {
        if (!ao->probing)
            MP_ERR(ao, "SDL_Init failed\n");
        uninit(ao);
        return -1;
    }

    struct mp_chmap_sel sel = {0};
    mp_chmap_sel_add_waveext_def(&sel);
    if (!ao_chmap_sel_adjust(ao, &sel, &ao->channels)) {
        uninit(ao);
        return -1;
    }

    ao->format = af_fmt_from_planar(ao->format);

    SDL_AudioSpec desired = {0};
    desired.format = AUDIO_S16SYS;
    for (int n = 0; fmtmap[n][0]; n++) {
        if (ao->format == fmtmap[n][0]) {
            desired.format = fmtmap[n][1];
            break;
        }
    }
    desired.freq = ao->samplerate;
    desired.channels = ao->channels.num;
    if (priv->buflen) {
        desired.samples = MPMIN(32768, ceil_power_of_two(ao->samplerate *
                                                         priv->buflen));
    }
    desired.callback = audio_callback;
    desired.userdata = ao;

    MP_VERBOSE(ao, "requested format: %d Hz, %d channels, %x, "
               "buffer size: %d samples\n",
               (int) desired.freq, (int) desired.channels,
               (int) desired.format, (int) desired.samples);

    SDL_AudioSpec obtained = desired;
    if (SDL_OpenAudio(&desired, &obtained)) {
        if (!ao->probing)
            MP_ERR(ao, "could not open audio: %s\n", SDL_GetError());
        uninit(ao);
        return -1;
    }

    MP_VERBOSE(ao, "obtained format: %d Hz, %d channels, %x, "
               "buffer size: %d samples\n",
               (int) obtained.freq, (int) obtained.channels,
               (int) obtained.format, (int) obtained.samples);

    // The sample count is usually the number of samples the callback requests,
    // which we assume is the period size. Normally, ao.c will allocate a large
    // enough buffer. But in case the period size should be pathologically
    // large, this will help.
    ao->device_buffer = 3 * obtained.samples;

    ao->format = 0;
    for (int n = 0; fmtmap[n][0]; n++) {
        if (obtained.format == fmtmap[n][1]) {
            ao->format = fmtmap[n][0];
            break;
        }
    }
    if (!ao->format) {
        if (!ao->probing)
            MP_ERR(ao, "could not find matching format\n");
        uninit(ao);
        return -1;
    }

    if (!ao_chmap_sel_get_def(ao, &sel, &ao->channels, obtained.channels)) {
        uninit(ao);
        return -1;
    }

    ao->samplerate = obtained.freq;

    priv->paused = 1;

    return 1;
}