#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qstr {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct dentry {int d_flags; TYPE_2__ d_name; TYPE_1__* d_op; } ;
struct TYPE_3__ {scalar_t__ (* d_compare ) (struct dentry const*,scalar_t__,int /*<<< orphan*/ ,struct qstr const*) ;} ;

/* Variables and functions */
 int DCACHE_OP_COMPARE ; 
 scalar_t__ dentry_cmp (struct dentry const*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ stub1 (struct dentry const*,scalar_t__,int /*<<< orphan*/ ,struct qstr const*) ; 

__attribute__((used)) static inline bool d_same_name(const struct dentry *dentry,
				const struct dentry *parent,
				const struct qstr *name)
{
	if (likely(!(parent->d_flags & DCACHE_OP_COMPARE))) {
		if (dentry->d_name.len != name->len)
			return false;
		return dentry_cmp(dentry, name->name, name->len) == 0;
	}
	return parent->d_op->d_compare(dentry,
				       dentry->d_name.len, dentry->d_name.name,
				       name) == 0;
}