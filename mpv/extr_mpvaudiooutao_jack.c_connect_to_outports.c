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
struct priv {int num_ports; int /*<<< orphan*/ * ports; int /*<<< orphan*/  client; TYPE_1__* opts; } ;
struct ao {struct priv* priv; } ;
struct TYPE_2__ {char* port; } ;

/* Variables and functions */
 char* JACK_DEFAULT_AUDIO_TYPE ; 
 int JackPortIsInput ; 
 int JackPortIsPhysical ; 
 int /*<<< orphan*/  MP_FATAL (struct ao*,char*) ; 
 int /*<<< orphan*/  free (char const**) ; 
 scalar_t__ jack_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 char** jack_get_ports (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  jack_port_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
connect_to_outports(struct ao *ao)
{
    struct priv *p = ao->priv;

    char *port_name = (p->opts->port && p->opts->port[0]) ? p->opts->port : NULL;
    const char **matching_ports = NULL;
    int port_flags = JackPortIsInput;
    int i;

    if (!port_name)
        port_flags |= JackPortIsPhysical;

    const char *port_type = JACK_DEFAULT_AUDIO_TYPE; // exclude MIDI ports
    matching_ports = jack_get_ports(p->client, port_name, port_type, port_flags);

    if (!matching_ports || !matching_ports[0]) {
        MP_FATAL(ao, "no ports to connect to\n");
        goto err_get_ports;
    }

    for (i = 0; i < p->num_ports && matching_ports[i]; i++) {
        if (jack_connect(p->client, jack_port_name(p->ports[i]),
                         matching_ports[i]))
        {
            MP_FATAL(ao, "connecting failed\n");
            goto err_connect;
        }
    }

    free(matching_ports);
    return 0;

err_connect:
    free(matching_ports);
err_get_ports:
    return -1;
}