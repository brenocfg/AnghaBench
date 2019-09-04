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

/* Variables and functions */
 struct device_node* of_parse_phandle (struct device_node*,char*,int) ; 

__attribute__((used)) static struct device_node *_opp_of_get_opp_desc_node(struct device_node *np,
						     int index)
{
	/* "operating-points-v2" can be an array for power domain providers */
	return of_parse_phandle(np, "operating-points-v2", index);
}