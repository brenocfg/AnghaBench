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
struct qstr {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int isofs_dentry_cmp_common (unsigned int,char const*,struct qstr const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
isofs_dentry_cmpi(const struct dentry *dentry,
		unsigned int len, const char *str, const struct qstr *name)
{
	return isofs_dentry_cmp_common(len, str, name, 0, 1);
}