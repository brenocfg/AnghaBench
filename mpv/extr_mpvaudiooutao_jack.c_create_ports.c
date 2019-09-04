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
struct priv {int num_ports; int /*<<< orphan*/ * ports; int /*<<< orphan*/  client; } ;
struct ao {struct priv* priv; } ;
typedef  int /*<<< orphan*/  pname ;

/* Variables and functions */
 int /*<<< orphan*/  JACK_DEFAULT_AUDIO_TYPE ; 
 int /*<<< orphan*/  JackPortIsOutput ; 
 int /*<<< orphan*/  MP_FATAL (struct ao*,char*) ; 
 int /*<<< orphan*/  jack_port_register (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
create_ports(struct ao *ao, int nports)
{
    struct priv *p = ao->priv;
    char pname[30];
    int i;

    for (i = 0; i < nports; i++) {
        snprintf(pname, sizeof(pname), "out_%d", i);
        p->ports[i] = jack_port_register(p->client, pname, JACK_DEFAULT_AUDIO_TYPE,
                                         JackPortIsOutput, 0);

        if (!p->ports[i]) {
            MP_FATAL(ao, "not enough ports available\n");
            goto err_port_register;
        }
    }

    p->num_ports = nports;
    return 0;

err_port_register:
    return -1;
}