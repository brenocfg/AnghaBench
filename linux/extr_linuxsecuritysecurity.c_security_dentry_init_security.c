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
typedef  int /*<<< orphan*/  u32 ;
struct qstr {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*,int,struct qstr const*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dentry_init_security ; 

int security_dentry_init_security(struct dentry *dentry, int mode,
					const struct qstr *name, void **ctx,
					u32 *ctxlen)
{
	return call_int_hook(dentry_init_security, -EOPNOTSUPP, dentry, mode,
				name, ctx, ctxlen);
}