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
struct hdac_hdmi_port {int /*<<< orphan*/  dapm; int /*<<< orphan*/  jack_pin; scalar_t__ is_connect; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdac_hdmi_port_dapm_update(struct hdac_hdmi_port *port)
{
	if (port->is_connect)
		snd_soc_dapm_enable_pin(port->dapm, port->jack_pin);
	else
		snd_soc_dapm_disable_pin(port->dapm, port->jack_pin);
	snd_soc_dapm_sync(port->dapm);
}