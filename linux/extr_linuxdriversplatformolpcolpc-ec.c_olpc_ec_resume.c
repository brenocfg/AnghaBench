#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct olpc_ec_priv {int suspended; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int (* resume ) (struct platform_device*) ;} ;

/* Variables and functions */
 TYPE_1__* ec_driver ; 
 struct olpc_ec_priv* platform_get_drvdata (struct platform_device*) ; 
 int stub1 (struct platform_device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int olpc_ec_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct olpc_ec_priv *ec = platform_get_drvdata(pdev);

	ec->suspended = false;
	return ec_driver->resume ? ec_driver->resume(pdev) : 0;
}