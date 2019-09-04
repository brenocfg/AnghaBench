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
typedef  int /*<<< orphan*/  u32 ;
struct il_priv {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  IL_INFO (char*,char const*) ; 
 struct il_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  il3945_hw_reg_set_txpower (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_strtoul (char*,char**,int) ; 

__attribute__((used)) static ssize_t
il3945_store_tx_power(struct device *d, struct device_attribute *attr,
		      const char *buf, size_t count)
{
	struct il_priv *il = dev_get_drvdata(d);
	char *p = (char *)buf;
	u32 val;

	val = simple_strtoul(p, &p, 10);
	if (p == buf)
		IL_INFO(": %s is not in decimal form.\n", buf);
	else
		il3945_hw_reg_set_txpower(il, val);

	return count;
}