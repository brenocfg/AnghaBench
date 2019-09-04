#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mpv_global {int dummy; } ;
struct mp_chmap {int num; } ;
struct encode_lavc_context {int dummy; } ;
struct ao {int samplerate; int format; int init_flags; char* device; int stream_silence; int period_size; char* redirect; int sstride; int num_planes; int bps; int device_buffer; int buffer; int def_buffer; TYPE_2__* api; TYPE_1__* driver; struct mp_chmap channels; int /*<<< orphan*/  api_priv; struct encode_lavc_context* encode_lavc_ctx; } ;
typedef  int /*<<< orphan*/  redirect ;
typedef  int /*<<< orphan*/  rdevice ;
struct TYPE_5__ {scalar_t__ (* init ) (struct ao*) ;int /*<<< orphan*/  options; int /*<<< orphan*/  priv_defaults; int /*<<< orphan*/  priv_size; } ;
struct TYPE_4__ {int encode; int (* init ) (struct ao*) ;int (* get_space ) (struct ao*) ;scalar_t__ play; } ;

/* Variables and functions */
 int AO_INIT_STREAM_SILENCE ; 
 void* MPMAX (int,int) ; 
 int /*<<< orphan*/  MP_ERR (struct ao*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*,int,...) ; 
 scalar_t__ af_fmt_is_planar (int) ; 
 int af_fmt_to_bytes (int) ; 
 int /*<<< orphan*/  af_fmt_to_str (int) ; 
 int af_format_sample_alignment (int) ; 
 struct ao* ao_alloc (int,struct mpv_global*,void (*) (void*),void*,char*) ; 
 TYPE_2__ ao_api_pull ; 
 TYPE_2__ ao_api_push ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_chmap_to_str (struct mp_chmap*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int stub1 (struct ao*) ; 
 int stub2 (struct ao*) ; 
 scalar_t__ stub3 (struct ao*) ; 
 int /*<<< orphan*/  talloc_free (struct ao*) ; 
 char* talloc_strdup (struct ao*,char*) ; 
 int /*<<< orphan*/  talloc_zero_size (struct ao*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ao *ao_init(bool probing, struct mpv_global *global,
                          void (*wakeup_cb)(void *ctx), void *wakeup_ctx,
                          struct encode_lavc_context *encode_lavc_ctx, int flags,
                          int samplerate, int format, struct mp_chmap channels,
                          char *dev, char *name)
{
    struct ao *ao = ao_alloc(probing, global, wakeup_cb, wakeup_ctx, name);
    if (!ao)
        return NULL;
    ao->samplerate = samplerate;
    ao->channels = channels;
    ao->format = format;
    ao->encode_lavc_ctx = encode_lavc_ctx;
    ao->init_flags = flags;
    if (ao->driver->encode != !!ao->encode_lavc_ctx)
        goto fail;

    MP_VERBOSE(ao, "requested format: %d Hz, %s channels, %s\n",
               ao->samplerate, mp_chmap_to_str(&ao->channels),
               af_fmt_to_str(ao->format));

    ao->device = talloc_strdup(ao, dev);

    ao->api = ao->driver->play ? &ao_api_push : &ao_api_pull;
    ao->api_priv = talloc_zero_size(ao, ao->api->priv_size);
    assert(!ao->api->priv_defaults && !ao->api->options);

    ao->stream_silence = flags & AO_INIT_STREAM_SILENCE;

    ao->period_size = 1;

    int r = ao->driver->init(ao);
    if (r < 0) {
        // Silly exception for coreaudio spdif redirection
        if (ao->redirect) {
            char redirect[80], rdevice[80];
            snprintf(redirect, sizeof(redirect), "%s", ao->redirect);
            snprintf(rdevice, sizeof(rdevice), "%s", ao->device ? ao->device : "");
            talloc_free(ao);
            return ao_init(probing, global, wakeup_cb, wakeup_ctx,
                           encode_lavc_ctx, flags, samplerate, format, channels,
                           rdevice, redirect);
        }
        goto fail;
    }

    if (ao->period_size < 1) {
        MP_ERR(ao, "Invalid period size set.\n");
        goto fail;
    }

    ao->sstride = af_fmt_to_bytes(ao->format);
    ao->num_planes = 1;
    if (af_fmt_is_planar(ao->format)) {
        ao->num_planes = ao->channels.num;
    } else {
        ao->sstride *= ao->channels.num;
    }
    ao->bps = ao->samplerate * ao->sstride;

    if (!ao->device_buffer && ao->driver->get_space)
        ao->device_buffer = ao->driver->get_space(ao);
    if (ao->device_buffer)
        MP_VERBOSE(ao, "device buffer: %d samples.\n", ao->device_buffer);
    ao->buffer = MPMAX(ao->device_buffer, ao->def_buffer * ao->samplerate);
    ao->buffer = MPMAX(ao->buffer, 1);

    int align = af_format_sample_alignment(ao->format);
    ao->buffer = (ao->buffer + align - 1) / align * align;
    MP_VERBOSE(ao, "using soft-buffer of %d samples.\n", ao->buffer);

    if (ao->api->init(ao) < 0)
        goto fail;
    return ao;

fail:
    talloc_free(ao);
    return NULL;
}