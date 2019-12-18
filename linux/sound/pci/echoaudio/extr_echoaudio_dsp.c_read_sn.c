#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct echoaudio {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ read_dsp (struct echoaudio*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_sn(struct echoaudio *chip)
{
	int i;
	u32 sn[6];

	for (i = 0; i < 5; i++) {
		if (read_dsp(chip, &sn[i])) {
			dev_err(chip->card->dev,
				"Failed to read serial number\n");
			return -EIO;
		}
	}
	dev_dbg(chip->card->dev,
		"Read serial number %08x %08x %08x %08x %08x\n",
		 sn[0], sn[1], sn[2], sn[3], sn[4]);
	return 0;
}