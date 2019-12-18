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
typedef  int /*<<< orphan*/  pa_stream ;
typedef  int /*<<< orphan*/  pa_sample_spec ;
typedef  int /*<<< orphan*/  pa_proplist ;
typedef  int /*<<< orphan*/  pa_channel_map ;

/* Variables and functions */
 int /*<<< orphan*/  pa_proplist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pa_stream_new_with_proplist (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pulseaudio_context ; 
 scalar_t__ pulseaudio_context_ready () ; 
 int /*<<< orphan*/  pulseaudio_lock () ; 
 int /*<<< orphan*/ * pulseaudio_properties () ; 
 int /*<<< orphan*/  pulseaudio_unlock () ; 

pa_stream *pulseaudio_stream_new(const char *name, const pa_sample_spec *ss,
				 const pa_channel_map *map)
{
	if (pulseaudio_context_ready() < 0)
		return NULL;

	pulseaudio_lock();

	pa_proplist *p = pulseaudio_properties();
	pa_stream *s = pa_stream_new_with_proplist(pulseaudio_context, name, ss,
						   map, p);
	pa_proplist_free(p);

	pulseaudio_unlock();
	return s;
}