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
typedef  int u8 ;
struct mipid_device {TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPID_CMD_RDDSDR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  ls041y3_esd_recover (struct mipid_device*) ; 
 int /*<<< orphan*/  mipid_read (struct mipid_device*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  set_sleep_mode (struct mipid_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ls041y3_esd_check_mode1(struct mipid_device *md)
{
	u8 state1, state2;

	mipid_read(md, MIPID_CMD_RDDSDR, &state1, 1);
	set_sleep_mode(md, 0);
	mipid_read(md, MIPID_CMD_RDDSDR, &state2, 1);
	dev_dbg(&md->spi->dev, "ESD mode 1 state1 %02x state2 %02x\n",
		state1, state2);
	/* Each sleep out command will trigger a self diagnostic and flip
	* Bit6 if the test passes.
	*/
	if (!((state1 ^ state2) & (1 << 6)))
		ls041y3_esd_recover(md);
}