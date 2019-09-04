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
struct mp_chmap {int dummy; } ;
struct ao {int samplerate; int format; struct mp_chmap channels; } ;

/* Variables and functions */

void ao_get_format(struct ao *ao,
                   int *samplerate, int *format, struct mp_chmap *channels)
{
    *samplerate = ao->samplerate;
    *format = ao->format;
    *channels = ao->channels;
}