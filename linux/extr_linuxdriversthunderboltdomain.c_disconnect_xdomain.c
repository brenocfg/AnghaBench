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
struct tb_xdomain {struct tb* tb; } ;
struct tb {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct tb_xdomain* tb_to_xdomain (struct device*) ; 
 int tb_xdomain_disable_paths (struct tb_xdomain*) ; 

__attribute__((used)) static int disconnect_xdomain(struct device *dev, void *data)
{
	struct tb_xdomain *xd;
	struct tb *tb = data;
	int ret = 0;

	xd = tb_to_xdomain(dev);
	if (xd && xd->tb == tb)
		ret = tb_xdomain_disable_paths(xd);

	return ret;
}