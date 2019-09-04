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
struct kernfs_node {int /*<<< orphan*/  ns; int /*<<< orphan*/  name; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int kernfs_name_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kernfs_node const*) ; 

__attribute__((used)) static int kernfs_sd_compare(const struct kernfs_node *left,
			     const struct kernfs_node *right)
{
	return kernfs_name_compare(left->hash, left->name, left->ns, right);
}