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
typedef  scalar_t__ uint32_t ;
struct priv {int stream_idx; int /*<<< orphan*/  stream; scalar_t__ spdif_hack; int /*<<< orphan*/  device; } ;
struct ao {int /*<<< orphan*/  format; struct priv* priv; } ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  int /*<<< orphan*/  AudioStreamID ;

/* Variables and functions */
 int /*<<< orphan*/  CA_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  CA_GET_ARY_O (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  CHECK_CA_ERROR (char*) ; 
 int /*<<< orphan*/  CHECK_CA_WARN (char*) ; 
 int /*<<< orphan*/  MP_ERR (struct ao*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*,int,...) ; 
 scalar_t__ af_fmt_is_pcm (int /*<<< orphan*/ ) ; 
 scalar_t__ ca_stream_supports_compressed (struct ao*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kAudioDevicePropertyStreams ; 
 int /*<<< orphan*/  kAudioStreamPropertyDirection ; 
 int /*<<< orphan*/  noErr ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int select_stream(struct ao *ao)
{
    struct priv *p = ao->priv;

    AudioStreamID *streams;
    size_t n_streams;
    OSStatus err;

    /* Get a list of all the streams on this device. */
    err = CA_GET_ARY_O(p->device, kAudioDevicePropertyStreams,
                       &streams, &n_streams);
    CHECK_CA_ERROR("could not get number of streams");
    for (int i = 0; i < n_streams; i++) {
        uint32_t direction;
        err = CA_GET(streams[i], kAudioStreamPropertyDirection, &direction);
        CHECK_CA_WARN("could not get stream direction");
        if (err == noErr && direction != 0) {
            MP_VERBOSE(ao, "Substream %d is not an output stream.\n", i);
            continue;
        }

        if (af_fmt_is_pcm(ao->format) || p->spdif_hack ||
            ca_stream_supports_compressed(ao, streams[i]))
        {
            MP_VERBOSE(ao, "Using substream %d/%zd.\n", i, n_streams);
            p->stream = streams[i];
            p->stream_idx = i;
            break;
        }
    }

    talloc_free(streams);

    if (p->stream_idx < 0) {
        MP_ERR(ao, "No useable substream found.\n");
        goto coreaudio_error;
    }

    return 0;

coreaudio_error:
    return -1;
}