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
struct m48t86_rtc_info {int /*<<< orphan*/  data_reg; int /*<<< orphan*/  index_reg; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct m48t86_rtc_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m48t86_writeb(struct device *dev,
			  unsigned char value, unsigned long addr)
{
	struct m48t86_rtc_info *info = dev_get_drvdata(dev);

	writeb(addr, info->index_reg);
	writeb(value, info->data_reg);
}