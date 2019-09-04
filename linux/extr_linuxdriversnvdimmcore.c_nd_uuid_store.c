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
typedef  int /*<<< orphan*/  uuid ;
typedef  int /*<<< orphan*/  u8 ;
struct device {scalar_t__ driver; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int nd_uuid_parse (struct device*,int /*<<< orphan*/ *,char const*,size_t) ; 

int nd_uuid_store(struct device *dev, u8 **uuid_out, const char *buf,
		size_t len)
{
	u8 uuid[16];
	int rc;

	if (dev->driver)
		return -EBUSY;

	rc = nd_uuid_parse(dev, uuid, buf, len);
	if (rc)
		return rc;

	kfree(*uuid_out);
	*uuid_out = kmemdup(uuid, sizeof(uuid), GFP_KERNEL);
	if (!(*uuid_out))
		return -ENOMEM;

	return 0;
}