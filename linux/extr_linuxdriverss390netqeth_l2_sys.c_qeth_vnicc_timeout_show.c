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
struct qeth_card {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct qeth_card* dev_get_drvdata (struct device*) ; 
 int qeth_l2_vnicc_get_timeout (struct qeth_card*,int*) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t qeth_vnicc_timeout_show(struct device *dev,
				       struct device_attribute *attr, char *buf)
{
	struct qeth_card *card = dev_get_drvdata(dev);
	u32 timeout;
	int rc;

	if (!card)
		return -EINVAL;

	rc = qeth_l2_vnicc_get_timeout(card, &timeout);
	if (rc == -EBUSY)
		return sprintf(buf, "n/a (BridgePort)\n");
	if (rc == -EOPNOTSUPP)
		return sprintf(buf, "n/a\n");
	return rc ? rc : sprintf(buf, "%d\n", timeout);
}