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
struct snd_motu {int dummy; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int EIO ; 
 unsigned int V2_CLOCK_RATE_MASK ; 
 unsigned int V2_CLOCK_RATE_SHIFT ; 
 int /*<<< orphan*/  V2_CLOCK_STATUS_OFFSET ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int* snd_motu_clock_rates ; 
 int snd_motu_transaction_read (struct snd_motu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int v2_get_clock_rate(struct snd_motu *motu, unsigned int *rate)
{
	__be32 reg;
	unsigned int index;
	int err;

	err = snd_motu_transaction_read(motu, V2_CLOCK_STATUS_OFFSET, &reg,
					sizeof(reg));
	if (err < 0)
		return err;

	index = (be32_to_cpu(reg) & V2_CLOCK_RATE_MASK) >> V2_CLOCK_RATE_SHIFT;
	if (index >= ARRAY_SIZE(snd_motu_clock_rates))
		return -EIO;

	*rate = snd_motu_clock_rates[index];

	return 0;
}