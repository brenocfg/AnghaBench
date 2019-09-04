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
struct TYPE_2__ {struct device* parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int bigmac_ether_init (struct platform_device*,struct platform_device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int bigmac_sbus_probe(struct platform_device *op)
{
	struct device *parent = op->dev.parent;
	struct platform_device *qec_op;

	qec_op = to_platform_device(parent);

	return bigmac_ether_init(op, qec_op);
}