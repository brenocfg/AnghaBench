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
struct snd_fw_async_midi_port {int idling; int error; int on_sysex; scalar_t__ running_status; } ;

/* Variables and functions */

void snd_fw_async_midi_port_init(struct snd_fw_async_midi_port *port)
{
	port->idling = true;
	port->error = false;
	port->running_status = 0;
	port->on_sysex = false;
}