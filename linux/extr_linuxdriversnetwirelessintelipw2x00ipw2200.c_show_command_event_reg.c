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
typedef  int u32 ;
struct ipw_priv {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_INTERNAL_CMD_EVENT ; 
 struct ipw_priv* dev_get_drvdata (struct device*) ; 
 int ipw_read_reg32 (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_command_event_reg(struct device *d,
				      struct device_attribute *attr, char *buf)
{
	u32 reg = 0;
	struct ipw_priv *p = dev_get_drvdata(d);

	reg = ipw_read_reg32(p, IPW_INTERNAL_CMD_EVENT);
	return sprintf(buf, "0x%08x\n", reg);
}