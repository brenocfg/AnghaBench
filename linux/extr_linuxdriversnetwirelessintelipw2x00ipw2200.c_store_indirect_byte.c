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
struct ipw_priv {int /*<<< orphan*/  status; int /*<<< orphan*/  indirect_byte; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_INDIRECT_BYTE ; 
 struct ipw_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strnlen (char const*,size_t) ; 

__attribute__((used)) static ssize_t store_indirect_byte(struct device *d,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	struct ipw_priv *priv = dev_get_drvdata(d);

	sscanf(buf, "%x", &priv->indirect_byte);
	priv->status |= STATUS_INDIRECT_BYTE;
	return strnlen(buf, count);
}