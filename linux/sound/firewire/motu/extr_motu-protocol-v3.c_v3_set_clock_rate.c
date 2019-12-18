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
struct snd_motu {int dummy; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 int EINTR ; 
 int EINVAL ; 
 int V3_CLOCK_RATE_MASK ; 
 int V3_CLOCK_RATE_SHIFT ; 
 int /*<<< orphan*/  V3_CLOCK_STATUS_OFFSET ; 
 int V3_FETCH_PCM_FRAMES ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 scalar_t__ msleep_interruptible (int) ; 
 unsigned int* snd_motu_clock_rates ; 
 int snd_motu_transaction_read (struct snd_motu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int snd_motu_transaction_write (struct snd_motu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int v3_set_clock_rate(struct snd_motu *motu, unsigned int rate)
{
	__be32 reg;
	u32 data;
	bool need_to_wait;
	int i, err;

	for (i = 0; i < ARRAY_SIZE(snd_motu_clock_rates); ++i) {
		if (snd_motu_clock_rates[i] == rate)
			break;
	}
	if (i == ARRAY_SIZE(snd_motu_clock_rates))
		return -EINVAL;

	err = snd_motu_transaction_read(motu, V3_CLOCK_STATUS_OFFSET, &reg,
					sizeof(reg));
	if (err < 0)
		return err;
	data = be32_to_cpu(reg);

	data &= ~(V3_CLOCK_RATE_MASK | V3_FETCH_PCM_FRAMES);
	data |= i << V3_CLOCK_RATE_SHIFT;

	need_to_wait = data != be32_to_cpu(reg);

	reg = cpu_to_be32(data);
	err = snd_motu_transaction_write(motu, V3_CLOCK_STATUS_OFFSET, &reg,
					 sizeof(reg));
	if (err < 0)
		return err;

	if (need_to_wait) {
		/* Cost expensive. */
		if (msleep_interruptible(4000) > 0)
			return -EINTR;
	}

	return 0;
}