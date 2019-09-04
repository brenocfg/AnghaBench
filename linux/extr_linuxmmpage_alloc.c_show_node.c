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
struct zone {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_NUMA ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_to_nid (struct zone*) ; 

__attribute__((used)) static inline void show_node(struct zone *zone)
{
	if (IS_ENABLED(CONFIG_NUMA))
		printk("Node %d ", zone_to_nid(zone));
}