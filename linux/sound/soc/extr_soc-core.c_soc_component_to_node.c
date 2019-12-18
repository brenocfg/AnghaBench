#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_component {TYPE_2__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {TYPE_1__* parent; struct device_node* of_node; } ;
struct TYPE_3__ {struct device_node* of_node; } ;

/* Variables and functions */

__attribute__((used)) static struct device_node
*soc_component_to_node(struct snd_soc_component *component)
{
	struct device_node *of_node;

	of_node = component->dev->of_node;
	if (!of_node && component->dev->parent)
		of_node = component->dev->parent->of_node;

	return of_node;
}