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
 int S_IFDIR ; 
 struct dentry* aafs_create (char const*,int,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *aafs_create_dir(const char *name, struct dentry *parent)
{
	return aafs_create(name, S_IFDIR | 0755, parent, NULL, NULL, NULL,
			   NULL);
}