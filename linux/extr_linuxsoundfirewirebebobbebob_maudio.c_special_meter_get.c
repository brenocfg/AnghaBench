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
typedef  int u32 ;
struct snd_bebob {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ METER_SIZE_SPECIAL ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int get_meter (struct snd_bebob*,void*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  special_meter_labels ; 

__attribute__((used)) static int
special_meter_get(struct snd_bebob *bebob, u32 *target, unsigned int size)
{
	__be16 *buf;
	unsigned int i, c, channels;
	int err;

	channels = ARRAY_SIZE(special_meter_labels) * 2;
	if (size < channels * sizeof(u32))
		return -EINVAL;

	/* omit last 4 bytes because it's clock info. */
	buf = kmalloc(METER_SIZE_SPECIAL - 4, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	err = get_meter(bebob, (void *)buf, METER_SIZE_SPECIAL - 4);
	if (err < 0)
		goto end;

	/* Its format is u16 and some channels are unknown. */
	i = 0;
	for (c = 2; c < channels + 2; c++)
		target[i++] = be16_to_cpu(buf[c]) << 16;
end:
	kfree(buf);
	return err;
}