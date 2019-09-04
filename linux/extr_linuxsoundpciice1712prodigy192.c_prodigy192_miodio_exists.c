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
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 unsigned char AK4114_REG_INT0_MASK ; 
 unsigned char const prodigy192_ak4114_read (struct snd_ice1712*,unsigned char) ; 
 int /*<<< orphan*/  prodigy192_ak4114_write (struct snd_ice1712*,unsigned char,unsigned char const) ; 

__attribute__((used)) static int prodigy192_miodio_exists(struct snd_ice1712 *ice)
{

	unsigned char orig_value;
	const unsigned char test_data = 0xd1;	/* random value */
	unsigned char addr = AK4114_REG_INT0_MASK; /* random SAFE address */
	int exists = 0;

	orig_value = prodigy192_ak4114_read(ice, addr);
	prodigy192_ak4114_write(ice, addr, test_data);
	if (prodigy192_ak4114_read(ice, addr) == test_data) {
		/* ak4114 seems to communicate, apparently exists */
		/* writing back original value */
		prodigy192_ak4114_write(ice, addr, orig_value);
		exists = 1;
	}
	return exists;
}