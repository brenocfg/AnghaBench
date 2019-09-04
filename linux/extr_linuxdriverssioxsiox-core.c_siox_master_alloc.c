#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device* parent; int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; } ;
struct siox_master {int busno; TYPE_1__ dev; int /*<<< orphan*/  poll_interval; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct siox_master*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 struct siox_master* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siox_bus_type ; 
 int /*<<< orphan*/  siox_master_type ; 

struct siox_master *siox_master_alloc(struct device *dev,
				      size_t size)
{
	struct siox_master *smaster;

	if (!dev)
		return NULL;

	smaster = kzalloc(sizeof(*smaster) + size, GFP_KERNEL);
	if (!smaster)
		return NULL;

	device_initialize(&smaster->dev);

	smaster->busno = -1;
	smaster->dev.bus = &siox_bus_type;
	smaster->dev.type = &siox_master_type;
	smaster->dev.parent = dev;
	smaster->poll_interval = DIV_ROUND_UP(HZ, 40);

	dev_set_drvdata(&smaster->dev, &smaster[1]);

	return smaster;
}