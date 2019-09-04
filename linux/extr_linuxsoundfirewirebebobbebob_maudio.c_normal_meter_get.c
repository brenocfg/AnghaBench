#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct snd_bebob_meter_spec {int num; scalar_t__ labels; } ;
struct snd_bebob {TYPE_1__* spec; } ;
struct TYPE_2__ {struct snd_bebob_meter_spec* meter; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  be32_to_cpus (int /*<<< orphan*/ *) ; 
 int get_meter (struct snd_bebob*,void*,unsigned int) ; 
 scalar_t__ solo_meter_labels ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
normal_meter_get(struct snd_bebob *bebob, u32 *buf, unsigned int size)
{
	const struct snd_bebob_meter_spec *spec = bebob->spec->meter;
	unsigned int c, channels;
	int err;

	channels = spec->num * 2;
	if (size < channels * sizeof(u32))
		return -EINVAL;

	err = get_meter(bebob, (void *)buf, size);
	if (err < 0)
		goto end;

	for (c = 0; c < channels; c++)
		be32_to_cpus(&buf[c]);

	/* swap stream channels because inverted */
	if (spec->labels == solo_meter_labels) {
		swap(buf[4], buf[6]);
		swap(buf[5], buf[7]);
	}
end:
	return err;
}