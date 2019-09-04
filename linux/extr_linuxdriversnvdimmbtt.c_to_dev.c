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
struct device {int dummy; } ;
struct arena_info {TYPE_1__* nd_btt; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */

__attribute__((used)) static struct device *to_dev(struct arena_info *arena)
{
	return &arena->nd_btt->dev;
}