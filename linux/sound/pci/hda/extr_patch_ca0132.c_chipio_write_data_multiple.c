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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int chipio_write_data (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 

__attribute__((used)) static int chipio_write_data_multiple(struct hda_codec *codec,
				      const u32 *data,
				      unsigned int count)
{
	int status = 0;

	if (data == NULL) {
		codec_dbg(codec, "chipio_write_data null ptr\n");
		return -EINVAL;
	}

	while ((count-- != 0) && (status == 0))
		status = chipio_write_data(codec, *data++);

	return status;
}