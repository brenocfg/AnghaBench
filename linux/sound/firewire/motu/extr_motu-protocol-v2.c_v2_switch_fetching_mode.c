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
struct snd_motu {int /*<<< orphan*/ * spec; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int V2_CLOCK_8PRE_FETCH_DISABLE ; 
 int V2_CLOCK_8PRE_FETCH_ENABLE ; 
 int /*<<< orphan*/  V2_CLOCK_STATUS_OFFSET ; 
 int V2_CLOCK_TRAVELER_FETCH_DISABLE ; 
 int V2_CLOCK_TRAVELER_FETCH_ENABLE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  snd_motu_spec_8pre ; 
 int /*<<< orphan*/  snd_motu_spec_traveler ; 
 int snd_motu_transaction_read (struct snd_motu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int snd_motu_transaction_write (struct snd_motu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int v2_switch_fetching_mode(struct snd_motu *motu, bool enable)
{
	__be32 reg;
	u32 data;
	int err = 0;

	if (motu->spec == &snd_motu_spec_traveler ||
	    motu->spec == &snd_motu_spec_8pre) {
		err = snd_motu_transaction_read(motu, V2_CLOCK_STATUS_OFFSET,
						&reg, sizeof(reg));
		if (err < 0)
			return err;
		data = be32_to_cpu(reg);

		if (motu->spec == &snd_motu_spec_traveler) {
			data &= ~(V2_CLOCK_TRAVELER_FETCH_DISABLE |
				  V2_CLOCK_TRAVELER_FETCH_ENABLE);

			if (enable)
				data |= V2_CLOCK_TRAVELER_FETCH_ENABLE;
			else
				data |= V2_CLOCK_TRAVELER_FETCH_DISABLE;
		} else if (motu->spec == &snd_motu_spec_8pre) {
			data &= ~(V2_CLOCK_8PRE_FETCH_DISABLE |
				  V2_CLOCK_8PRE_FETCH_ENABLE);

			if (enable)
				data |= V2_CLOCK_8PRE_FETCH_DISABLE;
			else
				data |= V2_CLOCK_8PRE_FETCH_ENABLE;
		}

		reg = cpu_to_be32(data);
		err = snd_motu_transaction_write(motu, V2_CLOCK_STATUS_OFFSET,
						 &reg, sizeof(reg));
	}

	return err;
}