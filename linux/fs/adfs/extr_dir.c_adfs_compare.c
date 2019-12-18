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
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int __adfs_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,unsigned int) ; 

__attribute__((used)) static int adfs_compare(const struct dentry *dentry, unsigned int len,
			const char *str, const struct qstr *qstr)
{
	return __adfs_compare(qstr->name, qstr->len, str, len);
}