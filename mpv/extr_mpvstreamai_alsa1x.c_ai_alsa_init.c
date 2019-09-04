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
struct TYPE_6__ {char* device; int /*<<< orphan*/  log; int /*<<< orphan*/  handle; } ;
struct TYPE_7__ {TYPE_1__ alsa; } ;
typedef  TYPE_2__ audio_in_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_PCM_STREAM_CAPTURE ; 
 int ai_alsa_setup (TYPE_2__*) ; 
 int snd_output_stdio_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_open (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_strerror (int) ; 
 int /*<<< orphan*/  stderr ; 

int ai_alsa_init(audio_in_t *ai)
{
    int err;

    const char *device = ai->alsa.device;
    if (!device)
        device = "default";

    err = snd_pcm_open(&ai->alsa.handle, device, SND_PCM_STREAM_CAPTURE, 0);
    if (err < 0) {
        MP_ERR(ai, "Error opening audio: %s\n", snd_strerror(err));
        return -1;
    }

    err = snd_output_stdio_attach(&ai->alsa.log, stderr, 0);

    if (err < 0) {
        return -1;
    }

    err = ai_alsa_setup(ai);

    return err;
}