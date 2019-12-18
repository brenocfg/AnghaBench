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
typedef  enum snd_motu_clock_source { ____Placeholder_snd_motu_clock_source } snd_motu_clock_source ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int SND_MOTU_CLOCK_SOURCE_ADAT_ON_OPT_A ; 
 int SND_MOTU_CLOCK_SOURCE_ADAT_ON_OPT_B ; 
 int SND_MOTU_CLOCK_SOURCE_INTERNAL ; 
 int SND_MOTU_CLOCK_SOURCE_SPDIF_ON_COAX ; 
 int SND_MOTU_CLOCK_SOURCE_SPDIF_ON_OPT_A ; 
 int SND_MOTU_CLOCK_SOURCE_SPDIF_ON_OPT_B ; 
 int SND_MOTU_CLOCK_SOURCE_UNKNOWN ; 
 int SND_MOTU_CLOCK_SOURCE_WORD_ON_BNC ; 
 int V3_CLOCK_SOURCE_MASK ; 
 int /*<<< orphan*/  V3_CLOCK_STATUS_OFFSET ; 
 int V3_NO_ADAT_OPT_IN_IFACE_A ; 
 int V3_NO_ADAT_OPT_IN_IFACE_B ; 
 int /*<<< orphan*/  V3_OPT_IFACE_MODE_OFFSET ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int snd_motu_transaction_read (struct snd_motu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int v3_get_clock_source(struct snd_motu *motu,
			       enum snd_motu_clock_source *src)
{
	__be32 reg;
	u32 data;
	unsigned int val;
	int err;

	err = snd_motu_transaction_read(motu, V3_CLOCK_STATUS_OFFSET, &reg,
					sizeof(reg));
	if (err < 0)
		return err;
	data = be32_to_cpu(reg);

	val = data & V3_CLOCK_SOURCE_MASK;
	if (val == 0x00) {
		*src = SND_MOTU_CLOCK_SOURCE_INTERNAL;
	} else if (val == 0x01) {
		*src = SND_MOTU_CLOCK_SOURCE_WORD_ON_BNC;
	} else if (val == 0x10) {
		*src = SND_MOTU_CLOCK_SOURCE_SPDIF_ON_COAX;
	} else if (val == 0x18 || val == 0x19) {
		err = snd_motu_transaction_read(motu, V3_OPT_IFACE_MODE_OFFSET,
						&reg, sizeof(reg));
		if (err < 0)
			return err;
		data = be32_to_cpu(reg);

		if (val == 0x18) {
			if (data & V3_NO_ADAT_OPT_IN_IFACE_A)
				*src = SND_MOTU_CLOCK_SOURCE_SPDIF_ON_OPT_A;
			else
				*src = SND_MOTU_CLOCK_SOURCE_ADAT_ON_OPT_A;
		} else {
			if (data & V3_NO_ADAT_OPT_IN_IFACE_B)
				*src = SND_MOTU_CLOCK_SOURCE_SPDIF_ON_OPT_B;
			else
				*src = SND_MOTU_CLOCK_SOURCE_ADAT_ON_OPT_B;
		}
	} else {
		*src = SND_MOTU_CLOCK_SOURCE_UNKNOWN;
	}

	return 0;
}