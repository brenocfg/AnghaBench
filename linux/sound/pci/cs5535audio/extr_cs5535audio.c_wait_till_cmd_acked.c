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
struct cs5535audio {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_CODEC_CNTL ; 
 unsigned int CMD_NEW ; 
 unsigned int cs_readl (struct cs5535audio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void wait_till_cmd_acked(struct cs5535audio *cs5535au, unsigned long timeout)
{
	unsigned int tmp;
	do {
		tmp = cs_readl(cs5535au, ACC_CODEC_CNTL);
		if (!(tmp & CMD_NEW))
			break;
		udelay(1);
	} while (--timeout);
	if (!timeout)
		dev_err(cs5535au->card->dev,
			"Failure writing to cs5535 codec\n");
}