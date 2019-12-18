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
struct priv {int num_ports; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  graph_latency_max; int /*<<< orphan*/ * ports; } ;
struct ao {scalar_t__ samplerate; struct priv* priv; } ;
typedef  double jack_nframes_t ;
typedef  double int64_t ;

/* Variables and functions */
 int MP_NUM_CHANNELS ; 
 int /*<<< orphan*/  ao_read_data (struct ao*,void**,double,double) ; 
 double atomic_load (int /*<<< orphan*/ *) ; 
 void* jack_port_get_buffer (int /*<<< orphan*/ ,double) ; 
 double mp_time_us () ; 

__attribute__((used)) static int process(jack_nframes_t nframes, void *arg)
{
    struct ao *ao = arg;
    struct priv *p = ao->priv;

    void *buffers[MP_NUM_CHANNELS];

    for (int i = 0; i < p->num_ports; i++)
        buffers[i] = jack_port_get_buffer(p->ports[i], nframes);

    jack_nframes_t jack_latency =
        atomic_load(&p->graph_latency_max) + atomic_load(&p->buffer_size);

    int64_t end_time = mp_time_us();
    end_time += (jack_latency + nframes) / (double)ao->samplerate * 1000000.0;

    ao_read_data(ao, buffers, nframes, end_time);

    return 0;
}