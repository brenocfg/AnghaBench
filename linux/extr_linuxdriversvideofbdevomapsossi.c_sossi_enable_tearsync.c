#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int tearsync_line; int tearsync_mode; TYPE_1__* fbdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 TYPE_2__ sossi ; 

__attribute__((used)) static int sossi_enable_tearsync(int enable, unsigned line)
{
	int mode;

	dev_dbg(sossi.fbdev->dev, "tearsync %d line %d\n", enable, line);
	if (line >= 1 << 11)
		return -EINVAL;
	if (enable) {
		if (line)
			mode = 2;		/* HS or VS */
		else
			mode = 3;		/* VS only */
	} else
		mode = 0;
	sossi.tearsync_line = line;
	sossi.tearsync_mode = mode;

	return 0;
}