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
struct il_priv {int retry_rate; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 struct il_priv* dev_get_drvdata (struct device*) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
il3945_store_retry_rate(struct device *d, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct il_priv *il = dev_get_drvdata(d);

	il->retry_rate = simple_strtoul(buf, NULL, 0);
	if (il->retry_rate <= 0)
		il->retry_rate = 1;

	return count;
}