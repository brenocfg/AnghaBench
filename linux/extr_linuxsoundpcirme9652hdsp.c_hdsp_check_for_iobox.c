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
struct hdsp {scalar_t__ io_type; int /*<<< orphan*/  state; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ H9632 ; 
 scalar_t__ H9652 ; 
 int HDSP_ConfigError ; 
 int /*<<< orphan*/  HDSP_FirmwareLoaded ; 
 int /*<<< orphan*/  HDSP_statusRegister ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hdsp_read (struct hdsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int hdsp_check_for_iobox (struct hdsp *hdsp)
{
	int i;

	if (hdsp->io_type == H9652 || hdsp->io_type == H9632) return 0;
	for (i = 0; i < 500; i++) {
		if (0 == (hdsp_read(hdsp, HDSP_statusRegister) &
					HDSP_ConfigError)) {
			if (i) {
				dev_dbg(hdsp->card->dev,
					"IO box found after %d ms\n",
						(20 * i));
			}
			return 0;
		}
		msleep(20);
	}
	dev_err(hdsp->card->dev, "no IO box connected!\n");
	hdsp->state &= ~HDSP_FirmwareLoaded;
	return -EIO;
}