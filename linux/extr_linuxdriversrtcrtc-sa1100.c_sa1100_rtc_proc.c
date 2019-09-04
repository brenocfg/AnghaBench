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
struct seq_file {int dummy; } ;
struct sa1100_rtc {int /*<<< orphan*/  rtsr; int /*<<< orphan*/  rttr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sa1100_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sa1100_rtc_proc(struct device *dev, struct seq_file *seq)
{
	struct sa1100_rtc *info = dev_get_drvdata(dev);

	seq_printf(seq, "trim/divider\t\t: 0x%08x\n", readl_relaxed(info->rttr));
	seq_printf(seq, "RTSR\t\t\t: 0x%08x\n", readl_relaxed(info->rtsr));

	return 0;
}