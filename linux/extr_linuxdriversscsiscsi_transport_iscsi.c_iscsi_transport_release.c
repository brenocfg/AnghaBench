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
struct iscsi_internal {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct iscsi_internal* dev_to_iscsi_internal (struct device*) ; 
 int /*<<< orphan*/  kfree (struct iscsi_internal*) ; 

__attribute__((used)) static void iscsi_transport_release(struct device *dev)
{
	struct iscsi_internal *priv = dev_to_iscsi_internal(dev);
	kfree(priv);
}