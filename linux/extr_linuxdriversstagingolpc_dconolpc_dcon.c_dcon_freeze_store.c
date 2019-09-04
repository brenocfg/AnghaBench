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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct dcon_priv {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DCON_SOURCE_CPU ; 
 int /*<<< orphan*/  DCON_SOURCE_DCON ; 
 int EINVAL ; 
 int /*<<< orphan*/  dcon_set_source (struct dcon_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcon_set_source_sync (struct dcon_priv*,int /*<<< orphan*/ ) ; 
 struct dcon_priv* dev_get_drvdata (struct device*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t dcon_freeze_store(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t count)
{
	struct dcon_priv *dcon = dev_get_drvdata(dev);
	unsigned long output;
	int ret;

	ret = kstrtoul(buf, 10, &output);
	if (ret)
		return ret;

	switch (output) {
	case 0:
		dcon_set_source(dcon, DCON_SOURCE_CPU);
		break;
	case 1:
		dcon_set_source_sync(dcon, DCON_SOURCE_DCON);
		break;
	case 2:  /* normally unused */
		dcon_set_source(dcon, DCON_SOURCE_DCON);
		break;
	default:
		return -EINVAL;
	}

	return count;
}