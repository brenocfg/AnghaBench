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
struct azx_dev {int dummy; } ;
struct azx {int num_streams; int driver_caps; } ;

/* Variables and functions */
 int AZX_DCAPS_SEPARATE_STREAM_TAG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  azx_bus (struct azx*) ; 
 int /*<<< orphan*/  azx_stream (struct azx_dev*) ; 
 struct azx_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_stream_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int stream_direction (struct azx*,int) ; 

int azx_init_streams(struct azx *chip)
{
	int i;
	int stream_tags[2] = { 0, 0 };

	/* initialize each stream (aka device)
	 * assign the starting bdl address to each stream (device)
	 * and initialize
	 */
	for (i = 0; i < chip->num_streams; i++) {
		struct azx_dev *azx_dev = kzalloc(sizeof(*azx_dev), GFP_KERNEL);
		int dir, tag;

		if (!azx_dev)
			return -ENOMEM;

		dir = stream_direction(chip, i);
		/* stream tag must be unique throughout
		 * the stream direction group,
		 * valid values 1...15
		 * use separate stream tag if the flag
		 * AZX_DCAPS_SEPARATE_STREAM_TAG is used
		 */
		if (chip->driver_caps & AZX_DCAPS_SEPARATE_STREAM_TAG)
			tag = ++stream_tags[dir];
		else
			tag = i + 1;
		snd_hdac_stream_init(azx_bus(chip), azx_stream(azx_dev),
				     i, dir, tag);
	}

	return 0;
}