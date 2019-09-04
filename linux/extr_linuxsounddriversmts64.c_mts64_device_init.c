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
struct parport {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MTS64_CMD_RESET ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mts64_disable_readout (struct parport*) ; 
 scalar_t__ mts64_probe (struct parport*) ; 
 int /*<<< orphan*/  mts64_write_command (struct parport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mts64_device_init(struct parport *p)
{
	int i;

	mts64_write_command(p, MTS64_CMD_RESET);

	for (i = 0; i < 64; ++i) {
		msleep(100);

		if (mts64_probe(p) == 0) {
			/* success */
			mts64_disable_readout(p);
			return 0;
		}
	}
	mts64_disable_readout(p);

	return -EIO;
}