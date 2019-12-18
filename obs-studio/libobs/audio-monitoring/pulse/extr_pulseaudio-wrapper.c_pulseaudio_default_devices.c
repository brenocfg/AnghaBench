#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pulseaudio_default_output {int /*<<< orphan*/  default_sink_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  default_sink_name; } ;
typedef  TYPE_1__ pa_server_info ;
typedef  int /*<<< orphan*/  pa_context ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pulseaudio_signal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pulseaudio_default_devices(pa_context *c, const pa_server_info *i,
				       void *userdata)
{
	UNUSED_PARAMETER(c);
	struct pulseaudio_default_output *d =
		(struct pulseaudio_default_output *)userdata;
	d->default_sink_name = bstrdup(i->default_sink_name);
	pulseaudio_signal(0);
}