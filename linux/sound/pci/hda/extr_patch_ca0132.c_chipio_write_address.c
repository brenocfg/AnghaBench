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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {unsigned int curr_chip_addx; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_ADDRESS_HIGH ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_ADDRESS_LOW ; 
 int chipio_send (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int chipio_write_address(struct hda_codec *codec,
				unsigned int chip_addx)
{
	struct ca0132_spec *spec = codec->spec;
	int res;

	if (spec->curr_chip_addx == chip_addx)
			return 0;

	/* send low 16 bits of the address */
	res = chipio_send(codec, VENDOR_CHIPIO_ADDRESS_LOW,
			  chip_addx & 0xffff);

	if (res != -EIO) {
		/* send high 16 bits of the address */
		res = chipio_send(codec, VENDOR_CHIPIO_ADDRESS_HIGH,
				  chip_addx >> 16);
	}

	spec->curr_chip_addx = (res < 0) ? ~0U : chip_addx;

	return res;
}