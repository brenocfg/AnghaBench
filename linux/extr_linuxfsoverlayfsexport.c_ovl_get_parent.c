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
 int /*<<< orphan*/  EIO ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static struct dentry *ovl_get_parent(struct dentry *dentry)
{
	/*
	 * ovl_fh_to_dentry() returns connected dir overlay dentries, so we
	 * should not get here.
	 */
	WARN_ON_ONCE(1);
	return ERR_PTR(-EIO);
}