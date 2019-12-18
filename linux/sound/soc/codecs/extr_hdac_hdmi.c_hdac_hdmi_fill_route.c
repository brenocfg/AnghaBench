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
struct snd_soc_dapm_route {char const* sink; char const* source; char const* control; int (* connected ) (struct snd_soc_dapm_widget*,struct snd_soc_dapm_widget*) ;} ;

/* Variables and functions */

__attribute__((used)) static void hdac_hdmi_fill_route(struct snd_soc_dapm_route *route,
		const char *sink, const char *control, const char *src,
		int (*handler)(struct snd_soc_dapm_widget *src,
			struct snd_soc_dapm_widget *sink))
{
	route->sink = sink;
	route->source = src;
	route->control = control;
	route->connected = handler;
}