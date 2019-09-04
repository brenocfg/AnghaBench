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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  RV3029_STATUS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rv3029_read_regs (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rv3029_get_sr(struct device *dev, u8 *buf)
{
	int ret = rv3029_read_regs(dev, RV3029_STATUS, buf, 1);

	if (ret < 0)
		return -EIO;
	dev_dbg(dev, "status = 0x%.2x (%d)\n", buf[0], buf[0]);
	return 0;
}