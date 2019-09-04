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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_genocide (struct dentry*) ; 
 int /*<<< orphan*/  shrink_dcache_parent (struct dentry*) ; 

__attribute__((used)) static void sel_remove_entries(struct dentry *de)
{
	d_genocide(de);
	shrink_dcache_parent(de);
}