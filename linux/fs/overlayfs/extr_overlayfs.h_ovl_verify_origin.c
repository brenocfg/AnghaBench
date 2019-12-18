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
 int /*<<< orphan*/  OVL_XATTR_ORIGIN ; 
 int ovl_verify_set_fh (struct dentry*,int /*<<< orphan*/ ,struct dentry*,int,int) ; 

__attribute__((used)) static inline int ovl_verify_origin(struct dentry *upper,
				    struct dentry *origin, bool set)
{
	return ovl_verify_set_fh(upper, OVL_XATTR_ORIGIN, origin, false, set);
}