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
struct device {int /*<<< orphan*/  driver; } ;
struct apr_driver {int (* probe ) (struct apr_device*) ;} ;
struct apr_device {int dummy; } ;

/* Variables and functions */
 int stub1 (struct apr_device*) ; 
 struct apr_device* to_apr_device (struct device*) ; 
 struct apr_driver* to_apr_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apr_device_probe(struct device *dev)
{
	struct apr_device *adev = to_apr_device(dev);
	struct apr_driver *adrv = to_apr_driver(dev->driver);

	return adrv->probe(adev);
}