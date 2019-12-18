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
typedef  int /*<<< orphan*/  pa_stream_flags_t ;
typedef  int /*<<< orphan*/  pa_stream ;
typedef  int /*<<< orphan*/  pa_buffer_attr ;
typedef  int int_fast32_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 char* bzalloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int pa_stream_connect_playback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pulseaudio_context_ready () ; 
 int /*<<< orphan*/  pulseaudio_lock () ; 
 int /*<<< orphan*/  pulseaudio_unlock () ; 
 int strlen (char const*) ; 

int_fast32_t pulseaudio_connect_playback(pa_stream *s, const char *name,
					 const pa_buffer_attr *attr,
					 pa_stream_flags_t flags)
{
	if (pulseaudio_context_ready() < 0)
		return -1;

	size_t dev_len = strlen(name) - 8;
	char *device = bzalloc(dev_len + 1);
	memcpy(device, name, dev_len);

	pulseaudio_lock();
	int_fast32_t ret =
		pa_stream_connect_playback(s, device, attr, flags, NULL, NULL);
	pulseaudio_unlock();

	bfree(device);
	return ret;
}