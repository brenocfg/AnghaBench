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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int chipio_write_address (struct hda_codec*,unsigned int) ; 
 int chipio_write_data (struct hda_codec*,unsigned int const) ; 

__attribute__((used)) static int chipio_write_no_mutex(struct hda_codec *codec,
		unsigned int chip_addx, const unsigned int data)
{
	int err;


	/* write the address, and if successful proceed to write data */
	err = chipio_write_address(codec, chip_addx);
	if (err < 0)
		goto exit;

	err = chipio_write_data(codec, data);
	if (err < 0)
		goto exit;

exit:
	return err;
}