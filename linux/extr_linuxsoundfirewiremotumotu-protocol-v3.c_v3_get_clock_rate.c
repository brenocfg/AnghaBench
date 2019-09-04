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
typedef  size_t u32 ;
struct snd_motu {int dummy; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 size_t ARRAY_SIZE (unsigned int*) ; 
 int EIO ; 
 size_t V3_CLOCK_RATE_MASK ; 
 size_t V3_CLOCK_RATE_SHIFT ; 
 int /*<<< orphan*/  V3_CLOCK_STATUS_OFFSET ; 
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int* snd_motu_clock_rates ; 
 int snd_motu_transaction_read (struct snd_motu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int v3_get_clock_rate(struct snd_motu *motu, unsigned int *rate)
{
	__be32 reg;
	u32 data;
	int err;

	err = snd_motu_transaction_read(motu, V3_CLOCK_STATUS_OFFSET, &reg,
					sizeof(reg));
	if (err < 0)
		return err;
	data = be32_to_cpu(reg);

	data = (data & V3_CLOCK_RATE_MASK) >> V3_CLOCK_RATE_SHIFT;
	if (data >= ARRAY_SIZE(snd_motu_clock_rates))
		return -EIO;

	*rate = snd_motu_clock_rates[data];

	return 0;
}