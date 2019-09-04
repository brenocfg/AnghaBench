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
struct ac97_codec_id {int id; unsigned int mask; } ;

/* Variables and functions */

__attribute__((used)) static const struct ac97_codec_id *look_for_codec_id(const struct ac97_codec_id *table,
						     unsigned int id)
{
	const struct ac97_codec_id *pid;

	for (pid = table; pid->id; pid++)
		if (pid->id == (id & pid->mask))
			return pid;
	return NULL;
}