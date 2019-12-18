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
struct kernfs_node {int dummy; } ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kernfs_node*,struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_init_security ; 

int security_kernfs_init_security(struct kernfs_node *kn_dir,
				  struct kernfs_node *kn)
{
	return call_int_hook(kernfs_init_security, 0, kn_dir, kn);
}