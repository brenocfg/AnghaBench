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
struct ao_push_state {int /*<<< orphan*/  thread; int /*<<< orphan*/  buffer; int /*<<< orphan*/  wakeup_pipe; int /*<<< orphan*/  wakeup; int /*<<< orphan*/  lock; } ;
struct ao {scalar_t__ device_buffer; int /*<<< orphan*/  buffer; int /*<<< orphan*/  samplerate; int /*<<< orphan*/  channels; int /*<<< orphan*/  format; struct ao_push_state* api_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct ao*,char*) ; 
 int /*<<< orphan*/  destroy_no_thread (struct ao*) ; 
 int /*<<< orphan*/  mp_audio_buffer_create (struct ao*) ; 
 int /*<<< orphan*/  mp_audio_buffer_preallocate_min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_audio_buffer_reinit_fmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_make_wakeup_pipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playthread ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ao*) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init(struct ao *ao)
{
    struct ao_push_state *p = ao->api_priv;

    pthread_mutex_init(&p->lock, NULL);
    pthread_cond_init(&p->wakeup, NULL);
    mp_make_wakeup_pipe(p->wakeup_pipe);

    if (ao->device_buffer <= 0) {
        MP_FATAL(ao, "Couldn't probe device buffer size.\n");
        goto err;
    }

    p->buffer = mp_audio_buffer_create(ao);
    mp_audio_buffer_reinit_fmt(p->buffer, ao->format,
                               &ao->channels, ao->samplerate);
    mp_audio_buffer_preallocate_min(p->buffer, ao->buffer);
    if (pthread_create(&p->thread, NULL, playthread, ao))
        goto err;
    return 0;
err:
    destroy_no_thread(ao);
    return -1;
}