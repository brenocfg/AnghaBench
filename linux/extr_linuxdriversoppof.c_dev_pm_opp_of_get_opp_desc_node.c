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
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 struct device_node* _opp_of_get_opp_desc_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct device_node *dev_pm_opp_of_get_opp_desc_node(struct device *dev)
{
	return _opp_of_get_opp_desc_node(dev->of_node, 0);
}