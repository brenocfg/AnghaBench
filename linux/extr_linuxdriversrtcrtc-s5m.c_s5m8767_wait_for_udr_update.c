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
struct s5m_rtc_info {int /*<<< orphan*/  dev; TYPE_1__* regs; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {unsigned int autoclear_udr_mask; int /*<<< orphan*/  udr_update; } ;

/* Variables and functions */
 int UDR_READ_RETRY_CNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int s5m8767_wait_for_udr_update(struct s5m_rtc_info *info)
{
	int ret, retry = UDR_READ_RETRY_CNT;
	unsigned int data;

	do {
		ret = regmap_read(info->regmap, info->regs->udr_update, &data);
	} while (--retry && (data & info->regs->autoclear_udr_mask) && !ret);

	if (!retry)
		dev_err(info->dev, "waiting for UDR update, reached max number of retries\n");

	return ret;
}