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
struct hdac_hdmi_port {int dummy; } ;
struct hdac_hdmi_pcm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdac_hdmi_jack_report (struct hdac_hdmi_pcm*,struct hdac_hdmi_port*,int) ; 
 int /*<<< orphan*/  hdac_hdmi_port_dapm_update (struct hdac_hdmi_port*) ; 

__attribute__((used)) static void hdac_hdmi_jack_report_sync(struct hdac_hdmi_pcm *pcm,
		struct hdac_hdmi_port *port, bool is_connect)
{
	hdac_hdmi_jack_report(pcm, port, is_connect);
	hdac_hdmi_port_dapm_update(port);
}