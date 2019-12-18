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
struct snd_rawmidi_substream {int /*<<< orphan*/  append; struct snd_rawmidi_runtime* runtime; } ;
struct snd_rawmidi_runtime {size_t avail; size_t avail_min; } ;

/* Variables and functions */

__attribute__((used)) static inline int snd_rawmidi_ready_append(struct snd_rawmidi_substream *substream,
					   size_t count)
{
	struct snd_rawmidi_runtime *runtime = substream->runtime;

	return runtime->avail >= runtime->avail_min &&
	       (!substream->append || runtime->avail >= count);
}