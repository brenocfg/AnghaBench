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
typedef  int /*<<< orphan*/  u64 ;
struct iscsi_endpoint {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* class_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct iscsi_endpoint* iscsi_dev_to_endpoint (struct device*) ; 
 int /*<<< orphan*/  iscsi_endpoint_class ; 
 int /*<<< orphan*/  iscsi_match_epid ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

struct iscsi_endpoint *iscsi_lookup_endpoint(u64 handle)
{
	struct iscsi_endpoint *ep;
	struct device *dev;

	dev = class_find_device(&iscsi_endpoint_class, NULL, &handle,
				iscsi_match_epid);
	if (!dev)
		return NULL;

	ep = iscsi_dev_to_endpoint(dev);
	/*
	 * we can drop this now because the interface will prevent
	 * removals and lookups from racing.
	 */
	put_device(dev);
	return ep;
}