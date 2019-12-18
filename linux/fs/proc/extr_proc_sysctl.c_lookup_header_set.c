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
struct ctl_table_set {int dummy; } ;
struct ctl_table_root {struct ctl_table_set* (* lookup ) (struct ctl_table_root*) ;struct ctl_table_set default_set; } ;

/* Variables and functions */
 struct ctl_table_set* stub1 (struct ctl_table_root*) ; 

__attribute__((used)) static struct ctl_table_set *
lookup_header_set(struct ctl_table_root *root)
{
	struct ctl_table_set *set = &root->default_set;
	if (root->lookup)
		set = root->lookup(root);
	return set;
}