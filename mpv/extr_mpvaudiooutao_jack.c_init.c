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
struct priv {int /*<<< orphan*/  client; int /*<<< orphan*/  num_ports; TYPE_1__* opts; } ;
struct mp_chmap_sel {int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  num; } ;
struct ao {TYPE_2__ channels; int /*<<< orphan*/  samplerate; int /*<<< orphan*/  format; int /*<<< orphan*/  global; struct priv* priv; } ;
typedef  int /*<<< orphan*/  jack_options_t ;
struct TYPE_4__ {int stdlayout; int /*<<< orphan*/  client_name; int /*<<< orphan*/  autostart; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_FORMAT_FLOATP ; 
 int /*<<< orphan*/  JackNoStartServer ; 
 int /*<<< orphan*/  JackNullOption ; 
 int /*<<< orphan*/  MP_FATAL (struct ao*,char*) ; 
 int /*<<< orphan*/  ao_chmap_sel_adjust (struct ao*,struct mp_chmap_sel*,TYPE_2__*) ; 
 int /*<<< orphan*/  ao_chmap_sel_get_def (struct ao*,struct mp_chmap_sel*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ao_jack_conf ; 
 int /*<<< orphan*/  buffer_size_cb ; 
 scalar_t__ create_ports (struct ao*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  graph_order_cb ; 
 int /*<<< orphan*/  jack_client_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jack_client_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jack_get_sample_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jack_set_buffer_size_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ao*) ; 
 int /*<<< orphan*/  jack_set_graph_order_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ao*) ; 
 int /*<<< orphan*/  jack_set_process_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ao*) ; 
 int /*<<< orphan*/  mp_chmap_sel_add_any (struct mp_chmap_sel*) ; 
 int /*<<< orphan*/  mp_chmap_sel_add_waveext (struct mp_chmap_sel*) ; 
 TYPE_1__* mp_get_config_group (struct ao*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process ; 

__attribute__((used)) static int init(struct ao *ao)
{
    struct priv *p = ao->priv;
    struct mp_chmap_sel sel = {0};
    jack_options_t open_options;

    p->opts = mp_get_config_group(ao, ao->global, &ao_jack_conf);

    ao->format = AF_FORMAT_FLOATP;

    switch (p->opts->stdlayout) {
    case 0:
        mp_chmap_sel_add_waveext(&sel);
        break;

    default:
        mp_chmap_sel_add_any(&sel);
    }

    if (!ao_chmap_sel_adjust(ao, &sel, &ao->channels))
        goto err_chmap;

    open_options = JackNullOption;
    if (!p->opts->autostart)
        open_options |= JackNoStartServer;

    p->client = jack_client_open(p->opts->client_name, open_options, NULL);
    if (!p->client) {
        MP_FATAL(ao, "cannot open server\n");
        goto err_client_open;
    }

    if (create_ports(ao, ao->channels.num))
        goto err_create_ports;

    jack_set_process_callback(p->client, process, ao);

    ao->samplerate = jack_get_sample_rate(p->client);

    jack_set_buffer_size_callback(p->client, buffer_size_cb, ao);
    jack_set_graph_order_callback(p->client, graph_order_cb, ao);

    if (!ao_chmap_sel_get_def(ao, &sel, &ao->channels, p->num_ports))
        goto err_chmap_sel_get_def;

    return 0;

err_chmap_sel_get_def:
err_create_ports:
    jack_client_close(p->client);
err_client_open:
err_chmap:
    return -1;
}