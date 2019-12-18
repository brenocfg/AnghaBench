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
struct hdsp {TYPE_1__* card; void* io_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* Digiface ; 
 int HDSP_DllError ; 
 int HDSP_PROGRAM ; 
 int HDSP_S200 ; 
 int HDSP_S300 ; 
 int /*<<< orphan*/  HDSP_SHORT_WAIT ; 
 int HDSP_S_LOAD ; 
 int /*<<< orphan*/  HDSP_control2Reg ; 
 int /*<<< orphan*/  HDSP_fifoData ; 
 int /*<<< orphan*/  HDSP_status2Register ; 
 int /*<<< orphan*/  HDSP_statusRegister ; 
 int HDSP_version1 ; 
 int HDSP_version2 ; 
 void* Multiface ; 
 void* RPM ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ hdsp_fifo_wait (struct hdsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hdsp_read (struct hdsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdsp_write (struct hdsp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdsp_get_iobox_version (struct hdsp *hdsp)
{
	if ((hdsp_read (hdsp, HDSP_statusRegister) & HDSP_DllError) != 0) {

		hdsp_write(hdsp, HDSP_control2Reg, HDSP_S_LOAD);
		hdsp_write(hdsp, HDSP_fifoData, 0);

		if (hdsp_fifo_wait(hdsp, 0, HDSP_SHORT_WAIT) < 0) {
			hdsp_write(hdsp, HDSP_control2Reg, HDSP_S300);
			hdsp_write(hdsp, HDSP_control2Reg, HDSP_S_LOAD);
		}

		hdsp_write(hdsp, HDSP_control2Reg, HDSP_S200 | HDSP_PROGRAM);
		hdsp_write (hdsp, HDSP_fifoData, 0);
		if (hdsp_fifo_wait(hdsp, 0, HDSP_SHORT_WAIT) < 0)
			goto set_multi;

		hdsp_write(hdsp, HDSP_control2Reg, HDSP_S_LOAD);
		hdsp_write(hdsp, HDSP_fifoData, 0);
		if (hdsp_fifo_wait(hdsp, 0, HDSP_SHORT_WAIT) == 0) {
			hdsp->io_type = Digiface;
			dev_info(hdsp->card->dev, "Digiface found\n");
			return 0;
		}

		hdsp_write(hdsp, HDSP_control2Reg, HDSP_S300);
		hdsp_write(hdsp, HDSP_control2Reg, HDSP_S_LOAD);
		hdsp_write(hdsp, HDSP_fifoData, 0);
		if (hdsp_fifo_wait(hdsp, 0, HDSP_SHORT_WAIT) == 0)
			goto set_multi;

		hdsp_write(hdsp, HDSP_control2Reg, HDSP_S300);
		hdsp_write(hdsp, HDSP_control2Reg, HDSP_S_LOAD);
		hdsp_write(hdsp, HDSP_fifoData, 0);
		if (hdsp_fifo_wait(hdsp, 0, HDSP_SHORT_WAIT) < 0)
			goto set_multi;

		hdsp->io_type = RPM;
		dev_info(hdsp->card->dev, "RPM found\n");
		return 0;
	} else {
		/* firmware was already loaded, get iobox type */
		if (hdsp_read(hdsp, HDSP_status2Register) & HDSP_version2)
			hdsp->io_type = RPM;
		else if (hdsp_read(hdsp, HDSP_status2Register) & HDSP_version1)
			hdsp->io_type = Multiface;
		else
			hdsp->io_type = Digiface;
	}
	return 0;

set_multi:
	hdsp->io_type = Multiface;
	dev_info(hdsp->card->dev, "Multiface found\n");
	return 0;
}