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
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  weight; } ;

/* Variables and functions */
 TYPE_1__* config_item_to_node (struct config_item*) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t node_weight_store(struct config_item *item, const char *buf,
				 size_t len)
{
	int rc = kstrtoint(buf, 0, &config_item_to_node(item)->weight);

	if (rc)
		return rc;
	return len;
}