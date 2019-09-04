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
struct device {int dummy; } ;
struct apr_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct apr_device*) ; 
 struct apr_device* to_apr_device (struct device*) ; 

__attribute__((used)) static void apr_dev_release(struct device *dev)
{
	struct apr_device *adev = to_apr_device(dev);

	kfree(adev);
}