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
struct node {int dummy; } ;
struct dt_info {int dummy; } ;
struct check {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_unique_unit_address_common (struct check*,struct dt_info*,struct node*,int) ; 

__attribute__((used)) static void check_unique_unit_address(struct check *c, struct dt_info *dti,
					      struct node *node)
{
	check_unique_unit_address_common(c, dti, node, false);
}