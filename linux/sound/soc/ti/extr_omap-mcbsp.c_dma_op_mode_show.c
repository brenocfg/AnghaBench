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
struct omap_mcbsp {int dma_op_mode; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 struct omap_mcbsp* dev_get_drvdata (struct device*) ; 
 char** dma_op_modes ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t dma_op_mode_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct omap_mcbsp *mcbsp = dev_get_drvdata(dev);
	int dma_op_mode, i = 0;
	ssize_t len = 0;
	const char * const *s;

	dma_op_mode = mcbsp->dma_op_mode;

	for (s = &dma_op_modes[i]; i < ARRAY_SIZE(dma_op_modes); s++, i++) {
		if (dma_op_mode == i)
			len += sprintf(buf + len, "[%s] ", *s);
		else
			len += sprintf(buf + len, "%s ", *s);
	}
	len += sprintf(buf + len, "\n");

	return len;
}