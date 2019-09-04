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
typedef  int /*<<< orphan*/  u32 ;
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {int /*<<< orphan*/  chipio_mutex; } ;

/* Variables and functions */
 int chipio_write_address (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int chipio_write_data_multiple (struct hda_codec*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int chipio_write_multiple(struct hda_codec *codec,
				 u32 chip_addx,
				 const u32 *data,
				 unsigned int count)
{
	struct ca0132_spec *spec = codec->spec;
	int status;

	mutex_lock(&spec->chipio_mutex);
	status = chipio_write_address(codec, chip_addx);
	if (status < 0)
		goto error;

	status = chipio_write_data_multiple(codec, data, count);
error:
	mutex_unlock(&spec->chipio_mutex);

	return status;
}