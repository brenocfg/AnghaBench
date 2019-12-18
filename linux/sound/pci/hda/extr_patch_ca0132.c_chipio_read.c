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
struct ca0132_spec {int /*<<< orphan*/  chipio_mutex; } ;

/* Variables and functions */
 int chipio_read_data (struct hda_codec*,unsigned int*) ; 
 int chipio_write_address (struct hda_codec*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int chipio_read(struct hda_codec *codec,
		unsigned int chip_addx, unsigned int *data)
{
	struct ca0132_spec *spec = codec->spec;
	int err;

	mutex_lock(&spec->chipio_mutex);

	/* write the address, and if successful proceed to write data */
	err = chipio_write_address(codec, chip_addx);
	if (err < 0)
		goto exit;

	err = chipio_read_data(codec, data);
	if (err < 0)
		goto exit;

exit:
	mutex_unlock(&spec->chipio_mutex);
	return err;
}