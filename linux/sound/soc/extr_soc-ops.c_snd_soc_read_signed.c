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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int snd_soc_component_read (struct snd_soc_component*,unsigned int,unsigned int*) ; 

__attribute__((used)) static int snd_soc_read_signed(struct snd_soc_component *component,
	unsigned int reg, unsigned int mask, unsigned int shift,
	unsigned int sign_bit, int *signed_val)
{
	int ret;
	unsigned int val;

	ret = snd_soc_component_read(component, reg, &val);
	if (ret < 0)
		return ret;

	val = (val >> shift) & mask;

	if (!sign_bit) {
		*signed_val = val;
		return 0;
	}

	/* non-negative number */
	if (!(val & BIT(sign_bit))) {
		*signed_val = val;
		return 0;
	}

	ret = val;

	/*
	 * The register most probably does not contain a full-sized int.
	 * Instead we have an arbitrary number of bits in a signed
	 * representation which has to be translated into a full-sized int.
	 * This is done by filling up all bits above the sign-bit.
	 */
	ret |= ~((int)(BIT(sign_bit) - 1));

	*signed_val = ret;

	return 0;
}